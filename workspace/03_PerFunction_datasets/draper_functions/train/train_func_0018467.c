champlain_bounding_box_extend (ChamplainBoundingBox *bbox,
    gdouble latitude, gdouble longitude)
{
  g_return_if_fail (CHAMPLAIN_BOUNDING_BOX (bbox));

  if (longitude < bbox->left)
    bbox->left = longitude;

  if (latitude < bbox->bottom)
    bbox->bottom = latitude;

  if (longitude > bbox->right)
    bbox->right = longitude;

  if (latitude > bbox->top)
    bbox->top = latitude;
}
