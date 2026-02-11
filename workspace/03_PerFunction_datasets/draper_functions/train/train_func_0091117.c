add(const char *t, int s, Fl_Callback *c,void *v,int f) {

  if (this != fl_menu_array_owner) {
    if (fl_menu_array_owner) {
      Fl_Menu_* o = fl_menu_array_owner;

      int value_offset = o->value_-local_array;
      int n = local_array_size;
      Fl_Menu_Item* newMenu = o->menu_ = new Fl_Menu_Item[n];
      memcpy(newMenu, local_array, n*sizeof(Fl_Menu_Item));
      if (o->value_) o->value_ = newMenu+value_offset;
    }
    if (menu_) {

      delete[] local_array;
      if (!alloc) copy(menu_);

      local_array_alloc = local_array_size = size();
      local_array = menu_;
    } else {

      alloc = 2;
      if (local_array) {
	menu_ = local_array;
      } else {
	local_array_alloc = 15;
	local_array = menu_ = new Fl_Menu_Item[local_array_alloc];
        memset(local_array, 0, sizeof(Fl_Menu_Item) * local_array_alloc);
      }
      memset(menu_, 0, sizeof(Fl_Menu_Item));
      local_array_size = 1;
    }
    fl_menu_array_owner = this;
  }
  int r = menu_->add(t,s,c,v,f);

  int value_offset = value_-menu_;
  menu_ = local_array;
  if (value_) value_ = menu_+value_offset;
  return r;
}
