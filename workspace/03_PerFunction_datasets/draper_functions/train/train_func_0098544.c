objobjnocol(void *obj1, void *obj2) {
  Model_object *o1 = (Model_object *)obj1;
  Model_object *o2 = (Model_object *)obj2;
  Rect a, b;

  if (IS_DELETED(o1) || IS_DELETED(o2) || o1 == o2)
    return TRUE;

  new_rect_from_object_cur(&a, o1);
  new_rect_from_object_cur(&b, o2);
  return !rects_collide(&a, &b);
}
