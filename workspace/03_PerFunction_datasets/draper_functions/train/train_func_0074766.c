isectionsWithXdir(GcPoint* startp, bool& negative_on_left)
{
  negative_on_left = false;

  if (ptrGmtr == NULL ) {
    return NULL;

  } else {
    return ptrGmtr->isectionsWithXdir(startp, negative_on_left);
  }
}
