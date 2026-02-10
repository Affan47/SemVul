_postorder(struct avln * ap, void *(*func) (), void *result) {
  if (ap != (struct avln *) (0)) {
    result = _postorder(ap->l, func, result);
    result = _postorder(ap->r, func, result);
    result = (*func) (ap->d, result);
  }
  return result;
}
