hwloc_libxml_export_file(hwloc_topology_t topology, const char *filename)
{
  xmlDocPtr doc;
  int ret;

  if (hwloc_plugin_check_namespace("xml_libxml", "hwloc__xml_verbose") < 0) {
    errno = ENOSYS;
    return -1;
  }

  errno = 0;

  doc = hwloc__libxml2_prepare_export(topology);
  ret = xmlSaveFormatFileEnc(filename, doc, "UTF-8", 1);
  xmlFreeDoc(doc);

  if (ret < 0) {
    if (!errno)

      errno = EINVAL;
    return ret;
  }
  return 0;
}
