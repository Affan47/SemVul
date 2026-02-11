delete_widget(Fl_Widget *wi) {
  if (!wi) return;

  if (num_dwidgets >= alloc_dwidgets) {
    Fl_Widget	**temp;

    temp = new Fl_Widget *[alloc_dwidgets + 10];
    if (alloc_dwidgets) {
      memcpy(temp, dwidgets, alloc_dwidgets * sizeof(Fl_Widget *));
      delete[] dwidgets;
    }

    dwidgets = temp;
    alloc_dwidgets += 10;
  }

  dwidgets[num_dwidgets] = wi;
  num_dwidgets ++;
}
