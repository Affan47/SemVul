doLeaf_series_pass1(TreeNode tree, Object *in, int nColors)
{
  Array array;
  Field field;
  Pointer *in_data[1];
  int in_knt[1];
  Type type;
  Category category;
  int rank, shape;
  Object attr, src_dependency_attr = NULL;
  int p_knt = -1;
  int float_pixels;

  if (DXGetObjectClass(in[0]) != CLASS_FIELD)
  {
    DXSetError(ERROR_BAD_CLASS, "\"rgb_image\" should be a field");
    goto error;
  }

  field = (Field)in[0];

  if (DXEmptyField(field))
    return tree;


  src_dependency_attr = DXGetComponentAttribute(field, "colors", "dep");
  if (! src_dependency_attr)
  {
    DXSetError(ERROR_MISSING_DATA,
	"\"rgb_image\" data component is missing a dependency attribute");
    goto error;
  }

  if (DXGetObjectClass(src_dependency_attr) != CLASS_STRING)
  {
    DXSetError(ERROR_BAD_CLASS, "\"rgb_image\" dependency attribute");
    goto error;
  }


  array = (Array)DXGetComponentValue(field, "positions");
  if (! array)
  {
    DXSetError(ERROR_BAD_CLASS,
	"\"rgb_image\" contains no positions component");
    goto error;
  }

  DXGetArrayInfo(array, &p_knt, NULL, NULL, NULL, NULL);

  array = (Array)DXGetComponentValue((Field)in[0], "colors");
  if (! array)
  {
    DXSetError(ERROR_MISSING_DATA, "\"rgb_image\" has no colors component");
    goto error;
  }

  if (DXGetObjectClass((Object)array) != CLASS_ARRAY)
  {
    DXSetError(ERROR_BAD_CLASS,
	"colors component of \"rgb_image\" should be an array");
    goto error;
  }


  attr = DXGetAttribute((Object)array, "dep");
  if (! attr)
  {
    DXSetError(ERROR_MISSING_DATA,
	"colors component of \"rgb_image\" has no dependency");
    goto error;
  }

  if (DXGetObjectClass(attr) != CLASS_STRING)
  {
    DXSetError(ERROR_BAD_CLASS,
	"dependency attribute of data component of \"rgb_image\"");
    goto error;
  }


  if (strcmp("positions", DXGetString((String)attr)))
  {
    DXSetError(ERROR_DATA_INVALID,
	"colors dependency of \"rgb_image\" must be positions");
    goto error;
  }

  DXGetArrayInfo(array, &in_knt[0], &type, &category, &rank, &shape);

  if ((type != TYPE_UBYTE && type != TYPE_FLOAT)
	 || category != CATEGORY_REAL ||
	 rank != 1 || shape != 3)
  {
    DXSetError(ERROR_DATA_INVALID, "input \"rgb_image\"");
    goto error;
  }

  in_data[0] = DXGetArrayData(array);
  if (! in_data[0])
     goto error;

  float_pixels = (type == TYPE_FLOAT);


  tree = QuantizeColors_series_pass1(tree, float_pixels,
    in_knt[0], (ubyte *)in_data[0], nColors);

  if (! tree)
     if (DXGetError()==ERROR_NONE)
        DXSetError(ERROR_INTERNAL, "error return from user routine");


error:
  return tree;
}
