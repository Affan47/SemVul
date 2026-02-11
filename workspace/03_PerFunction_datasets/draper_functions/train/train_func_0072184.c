iImageInit(imImage* image, int width, int height, int color_space, int data_type, int has_alpha)
{
  assert(width>0);
  assert(height>0);
  assert(color_space >= IM_RGB && color_space <= IM_XYZ);
  assert(data_type >= IM_BYTE && data_type <= IM_CFLOAT);

  image->width = width;
  image->height = height;
  image->color_space = color_space;
  image->data_type = data_type;
  image->has_alpha = has_alpha;

  image->depth = imColorModeDepth(color_space);
  image->line_size = image->width * imDataTypeSize(data_type);
  image->plane_size = image->line_size * image->height;
  image->size = image->plane_size * image->depth;
  image->count = image->width * image->height;

  int depth = image->depth+1;

  if (image->data)
  {

    void* data0 = image->data[0];

    free(image->data);
    image->data = (void**)malloc(depth * sizeof(void*));

    image->data[0] = data0;
  }
  else
    image->data = (void**)malloc(depth * sizeof(void*));
}
