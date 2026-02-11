BBoxMinMaxND(BBox *bbox, HPointN **min, HPointN **max)
{
  if (bbox != NULL) {
    *min = HPtNCopy(bbox->min, *min);
    *max = HPtNCopy(bbox->max, *max);
  } else {
    *min = NULL;
    *max = NULL;
  }
  return bbox;
}
