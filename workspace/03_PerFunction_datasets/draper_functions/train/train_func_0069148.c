hwloc_obj_snprintf(char *string, size_t size,
    struct hwloc_topology *topology __hwloc_attribute_unused, struct hwloc_obj *l, const char *_indexprefix, int verbose)
{
  const char *indexprefix = _indexprefix ? _indexprefix : "#";
  char os_index[12] = "";
  char type[64];
  char attr[128];
  int attrlen;

  if (l->os_index != (unsigned) -1) {
    hwloc_snprintf(os_index, 12, "%s%u", indexprefix, l->os_index);
  }

  hwloc_obj_type_snprintf(type, sizeof(type), l, verbose);
  attrlen = hwloc_obj_attr_snprintf(attr, sizeof(attr), l, " ", verbose);

  if (attrlen > 0)
    return hwloc_snprintf(string, size, "%s%s(%s)", type, os_index, attr);
  else
    return hwloc_snprintf(string, size, "%s%s", type, os_index);
}
