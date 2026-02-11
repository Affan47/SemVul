set(const SbXfBox3f & boundingbox,
                        SbBool centerset,
                        const SbVec3f & centerpoint)
{
  PRIVATE(this)->bbox = boundingbox;
  PRIVATE(this)->localbbox = boundingbox.project();
  PRIVATE(this)->centerset = centerset ? 1 : 0;
  if (centerset) { PRIVATE(this)->centerpoint = centerpoint; }
}
