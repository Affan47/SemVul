get_src_pad (GstElement * element)
{
  GstIterator *it;
  GstIteratorResult itres;
  GstPad *srcpad;

  it = gst_element_iterate_src_pads (element);
  itres = gst_iterator_next (it, (gpointer) & srcpad);
  if (itres != GST_ITERATOR_OK) {
    GST_DEBUG ("%s doesn't have a src pad !", GST_ELEMENT_NAME (element));
    srcpad = NULL;
  }
  gst_iterator_free (it);
  return srcpad;
}
