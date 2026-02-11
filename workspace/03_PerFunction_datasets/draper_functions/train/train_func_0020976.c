idle(void*) {
  if (!mbrot.d->idle() && !(jbrot.d && jbrot.d->idle())) Fl::remove_idle(idle);
}
