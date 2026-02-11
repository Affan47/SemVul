copy_label(const char *a) {

  if ((flags() & COPIED_LABEL) && (label_.value == a))
    return;
  if (a) {
    label(strdup(a));
    set_flag(COPIED_LABEL);
  } else {
    label(0);
  }
}
