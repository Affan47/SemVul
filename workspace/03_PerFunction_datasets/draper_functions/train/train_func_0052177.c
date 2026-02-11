static_value(const char* str, int len) {
  clear_changed();
  if (undowidget == this) undowidget = 0;
  if (str == value_ && len == size_) return 0;
  if (len) {
    if (xscroll_ || yscroll_) {
      xscroll_ = yscroll_ = 0;
      minimal_update(0);
    } else {
      int i = 0;

      if (value_) {
	for (; i<size_ && i<len && str[i]==value_[i]; i++);
	if (i==size_ && i==len) return 0;
      }
      minimal_update(i);
    }
    value_ = str;
    size_ = len;
  } else {
    if (!size_) return 0;
    size_ = 0;
    value_ = "";
    xscroll_ = yscroll_ = 0;
    minimal_update(0);
  }
  position(readonly() ? 0 : size());
  return 1;
}
