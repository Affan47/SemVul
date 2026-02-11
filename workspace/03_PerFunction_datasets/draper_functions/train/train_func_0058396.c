hwloc_libxml2_disable_stderrwarnings(void)
{
  static int first = 1;
  if (first) {
    xmlSetGenericErrorFunc(NULL, hwloc__xml_verbose() ? xmlGenericError : hwloc_libxml2_error_callback);
    first = 0;
  }
}
