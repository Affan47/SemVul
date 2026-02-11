binary_get_element(PlyFile *plyfile, char *elem_ptr)
{
  int j,k;
  PlyElement *elem;
  PlyProperty *prop;
  FILE *fp = plyfile->fp;
  char *elem_data,*item=NULL;
  char *item_ptr;
  int item_size;
  int int_val;
  unsigned int uint_val;
  double double_val;
  int list_count;
  int store_it;
  char **store_array;
  char *other_data=NULL;
  int other_flag;


  elem = plyfile->which_elem;


  if (elem->other_offset != NO_OTHER_PROPS) {
    char **ptr;
    other_flag = 1;

    other_data = (char *) myalloc (elem->other_size);

    ptr = (char **) (elem_ptr + elem->other_offset);
    *ptr = other_data;
  }
  else
    other_flag = 0;


  for (j = 0; j < elem->nprops; j++) {

    prop = elem->props[j];
    store_it = (elem->store_prop[j] | other_flag);


    if (elem->store_prop[j])
      elem_data = elem_ptr;
    else
      elem_data = other_data;

    if (prop->is_list) {


      get_binary_item (fp, plyfile->file_type, prop->count_external,
                      &int_val, &uint_val, &double_val);
      if (store_it) {
        item = elem_data + prop->count_offset;
        store_item(item, prop->count_internal, int_val, uint_val, double_val);
      }


      list_count = int_val;
      item_size = ply_type_size[prop->internal_type];
      store_array = (char **) (elem_data + prop->offset);
      if (list_count == 0) {
        if (store_it)
          *store_array = NULL;
      }
      else {
        if (store_it) {
          item_ptr = (char *) myalloc (sizeof (char) * item_size * list_count);
          item = item_ptr;
          *store_array = item_ptr;
        }


        for (k = 0; k < list_count; k++) {
          get_binary_item (fp, plyfile->file_type, prop->external_type,
                          &int_val, &uint_val, &double_val);
          if (store_it) {
            store_item (item, prop->internal_type,
                        int_val, uint_val, double_val);
            item += item_size;
          }
        }
      }

    }
    else {
      get_binary_item (fp, plyfile->file_type, prop->external_type,
                      &int_val, &uint_val, &double_val);
      if (store_it) {
        item = elem_data + prop->offset;
        store_item (item, prop->internal_type, int_val, uint_val, double_val);
      }
    }

  }
}
