hwloc_nolibxml_backend_init(struct hwloc_xml_backend_data_s *bdata,
			    const char *xmlpath, const char *xmlbuffer, int xmlbuflen)
{
  struct hwloc__nolibxml_backend_data_s *nbdata = malloc(sizeof(*nbdata));

  if (!nbdata)
    goto out;
  bdata->data = nbdata;

  if (xmlbuffer) {
    nbdata->buffer = malloc(xmlbuflen);
    if (!nbdata->buffer)
      goto out_with_nbdata;
    nbdata->buflen = xmlbuflen;
    memcpy(nbdata->buffer, xmlbuffer, xmlbuflen);

  } else {
    int err = hwloc_nolibxml_read_file(xmlpath, &nbdata->buffer, &nbdata->buflen);
    if (err < 0)
      goto out_with_nbdata;
  }


  nbdata->copy = malloc(nbdata->buflen);
  if (!nbdata->copy)
    goto out_with_buffer;

  bdata->look_init = hwloc_nolibxml_look_init;
  bdata->look_failed = hwloc_nolibxml_look_failed;
  bdata->backend_exit = hwloc_nolibxml_backend_exit;
  return 0;

out_with_buffer:
  free(nbdata->buffer);
out_with_nbdata:
  free(nbdata);
out:
  return -1;
}
