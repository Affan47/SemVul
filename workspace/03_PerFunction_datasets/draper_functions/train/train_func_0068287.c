insert(
  Fl_Menu_Item* array, int size,
  int n,
  const char *text,
  int flags
) {
  if (array == local_array && size >= local_array_alloc) {
    local_array_alloc = 2*size;
    Fl_Menu_Item* newarray = new Fl_Menu_Item[local_array_alloc];
    memmove(newarray, array, size*sizeof(Fl_Menu_Item));
    delete[] local_array;
    local_array = array = newarray;
  }

  memmove(array+n+1, array+n, sizeof(Fl_Menu_Item)*(size-n));

  Fl_Menu_Item* m = array+n;
  m->text = text ? strdup(text) : 0;
  m->shortcut_ = 0;
  m->callback_ = 0;
  m->user_data_ = 0;
  m->flags = flags;
  m->labeltype_ = m->labelfont_ = m->labelsize_ = m->labelcolor_ = 0;
  return array;
}
