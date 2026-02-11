gt_tag_value_map_get(const GtTagValueMap map, const char *tag)
{
  gt_assert(map && tag && strlen(tag));
  return get_value(map, tag, NULL);
}
