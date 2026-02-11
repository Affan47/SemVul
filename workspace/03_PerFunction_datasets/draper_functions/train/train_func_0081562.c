resolve_list_pair(Model *m, List *l1, List *l2, Collide_func f) {
  List_ptr *ptr = new_list_ptr(l1);

  if (list_ptr_first(ptr)) {
    do {
      if (resolve_object_with_list(m, list_ptr_get_data(ptr), l2, f)) {
        del_list_ptr(ptr);
        return TRUE;
      }
    } while (list_ptr_next(ptr));
  }

  del_list_ptr(ptr);
  return FALSE;
}
