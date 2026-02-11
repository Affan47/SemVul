hwloc__nolibxml_export_add_content(hwloc__xml_export_state_t state, const char *buffer, size_t length)
{
  hwloc__nolibxml_export_state_data_t ndata = (void *) state->data;
  int res;

  assert(!ndata->nr_children);
  if (!ndata->has_content) {
    res = hwloc_snprintf(ndata->buffer, ndata->remaining, ">");
    hwloc__nolibxml_export_update_buffer(ndata, res);
  }
  ndata->has_content = 1;

  res = hwloc_snprintf(ndata->buffer, ndata->remaining, buffer, length);
  hwloc__nolibxml_export_update_buffer(ndata, res);
}
