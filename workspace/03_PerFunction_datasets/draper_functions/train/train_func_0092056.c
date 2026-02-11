hwloc_libxml_backend_init(struct hwloc_xml_backend_data_s *bdata,
			  const char *xmlpath, const char *xmlbuffer, int xmlbuflen)
{
  xmlDoc *doc = NULL;

  if (hwloc_plugin_check_namespace("xml_libxml", "hwloc__xml_verbose") < 0) {
    errno = ENOSYS;
    return -1;
  }

  LIBXML_TEST_VERSION;
  hwloc_libxml2_disable_stderrwarnings();

  errno = 0;

  if (xmlpath)
    doc = xmlReadFile(xmlpath, NULL, 0);
  else if (xmlbuffer)
    doc = xmlReadMemory(xmlbuffer, xmlbuflen, "", NULL, 0);

  if (!doc) {
    if (!errno)

    errno = EINVAL;
    return -1;
  }

  bdata->look_init = hwloc_libxml_look_init;
  bdata->look_failed = NULL;
  bdata->backend_exit = hwloc_libxml_backend_exit;
  bdata->data = doc;
  return 0;
}
