fibheap_delete_node (fibheap_t heap, fibnode_t node)
{
  void *ret = node->data;


  fibheap_replace_key (heap, node, FIBHEAPKEY_MIN);
  if (node != heap->min)
    {
      fprintf (stderr, "Can't force minimum on fibheap.\n");
      abort ();
    }
  fibheap_extract_min (heap);

  return ret;
}
