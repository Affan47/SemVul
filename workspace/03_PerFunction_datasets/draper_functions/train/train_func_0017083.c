statusbar_setitem(int element, bx_bool active, bx_bool w)
{
  if (element < 0) {
    for (unsigned i = 0; i < statusitem_count; i++) {
      set_status_text(i+1, statusitem_text[i], active, w);
    }
  } else if ((unsigned)element < statusitem_count) {
    set_status_text(element+1, statusitem_text[element], active, w);
  }
}
