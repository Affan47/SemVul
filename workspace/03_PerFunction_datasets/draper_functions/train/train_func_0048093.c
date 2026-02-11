maybe_do_callback() {
  if (changed() || (when()&FL_WHEN_NOT_CHANGED)) {
    do_callback();
  }
}
