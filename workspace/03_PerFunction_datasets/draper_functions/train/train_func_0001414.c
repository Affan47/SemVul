unblock_children (GnlComposition * comp)
{
  GstIterator *children;

  children = gst_bin_iterate_elements (GST_BIN (comp));

retry:
  if (G_UNLIKELY (gst_iterator_fold (children,
              (GstIteratorFoldFunction) unblock_child_pads, NULL,
              comp) == GST_ITERATOR_RESYNC)) {
    gst_iterator_resync (children);
    goto retry;
  }
  gst_iterator_free (children);
}
