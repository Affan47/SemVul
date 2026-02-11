hwloc___nolibxml_prepare_export_diff(hwloc_topology_diff_t diff, const char *refname, char *xmlbuffer, int buflen)
{
  struct hwloc__xml_export_state_s state, childstate;
  hwloc__nolibxml_export_state_data_t ndata = (void *) &state.data;
  int res;

  assert(sizeof(*ndata) <= sizeof(state.data));

  state.new_child = hwloc__nolibxml_export_new_child;
  state.new_prop = hwloc__nolibxml_export_new_prop;
  state.add_content = hwloc__nolibxml_export_add_content;
  state.end_object = hwloc__nolibxml_export_end_object;

  ndata->indent = 0;
  ndata->written = 0;
  ndata->buffer = xmlbuffer;
  ndata->remaining = buflen;

  ndata->nr_children = 1;
  ndata->has_content = 0;

  res = hwloc_snprintf(ndata->buffer, ndata->remaining,
		 "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
		 "<!DOCTYPE topologydiff SYSTEM \"hwloc.dtd\">\n");
  hwloc__nolibxml_export_update_buffer(ndata, res);
  hwloc__nolibxml_export_new_child(&state, &childstate, "topologydiff");
  if (refname)
    hwloc__nolibxml_export_new_prop(&childstate, "refname", refname);
  hwloc__xml_export_diff (&childstate, diff);
  hwloc__nolibxml_export_end_object(&childstate, "topologydiff");

  return ndata->written+1;
}
