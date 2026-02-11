tp_heap_destroy (TpHeap * heap)
{
  g_return_if_fail (heap != NULL);

  if (heap->destructor)
    {
      guint i;

      for (i = 0; i < heap->data->len; i++)
        {
          (heap->destructor) (g_ptr_array_index (heap->data, i));
        }
    }

  g_ptr_array_unref (heap->data);
  g_slice_free (TpHeap, heap);
}
