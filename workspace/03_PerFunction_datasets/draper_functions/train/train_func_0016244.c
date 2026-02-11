hb_face_make_immutable (hb_face_t *face)
{
  if (hb_object_is_inert (face))
    return;

  face->immutable = true;
}
