clear() {
  savedfocus_ = 0;
  resizable_ = this;
  init_sizes();


  Fl_Widget *pushed = Fl::pushed();
  if (contains(pushed)) pushed = this;
  Fl::pushed(this);


#define REVERSE_CHILDREN
#ifdef  REVERSE_CHILDREN


  if (children_ > 1) {
    Fl_Widget *temp;
    Fl_Widget **a = (Fl_Widget**)array();
    for (int i=0,j=children_-1; i<children_/2; i++,j--) {
      temp = a[i];
      a[i] = a[j];
      a[j] = temp;
    }
  }
#endif

  while (children_) {
    int idx = children_-1;
    Fl_Widget* w = child(idx);
    if (w->parent()==this) {
      if (children_>2) {
        w->parent_ = 0;
        children_--;
      } else {
        remove(idx);
      }
      delete w;
    } else {
      remove(idx);
    }
  }

  if (pushed != this) Fl::pushed(pushed);

}
