get_ref_name_type(char *name, char *type, int len, int index)
{
struct constant_fieldref_t *constant_fieldref;
struct constant_methodref_t *constant_methodref;
struct constant_nameandtype_t *constant_nameandtype;
int tag,offset;
void *heap;


  name[0] = 0;
  type[0] = 0;


  while(1)
  {
    if (index > constant_pool_count) { return -1; }

    offset = constant_pool[index];
    heap = (void *)(((uint8_t *)constants_heap) + offset);
    tag = constants_heap[offset];

    if (tag == CONSTANT_FIELDREF)
    {
      constant_fieldref = (constant_fieldref_t *)heap;
      index = constant_fieldref->name_and_type_index;


      if (constant_fieldref->class_index != this_class)
      {
        get_class_name(name, len, constant_fieldref->class_index);
        printf("  class_name='%s' %d\n", name, constant_fieldref->class_index);
        strcat(name, "_");
      }
    }
      else
    if (tag == CONSTANT_METHODREF)
    {
      constant_methodref = (constant_methodref_t *)heap;
      index = constant_methodref->name_and_type_index;
    }
      else
    if (tag == CONSTANT_NAMEANDTYPE)
    {
      constant_nameandtype = (constant_nameandtype_t *)heap;
      int class_name_len = strlen(name);
      get_name_constant(name + class_name_len, len - class_name_len, constant_nameandtype->name_index);
      get_name_constant(type, len, constant_nameandtype->descriptor_index);
      return 0;
    }
      else
    {
      break;
    }
  }

  return -1;
}
