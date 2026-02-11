decoder_init_data_iterator(
                                                long start_of_encoding,
                                                long end_of_encoding,
                                                const GtStr *filename)
{
  HcrHuffDataIterator *data_iter = gt_malloc(sizeof (*data_iter));
  data_iter->path = gt_str_get(filename);
  data_iter->pos = data_iter->start = (size_t) start_of_encoding;
  data_iter->end = (size_t) end_of_encoding;
  data_iter->pages_per_chunk = HCR_PAGES_PER_CHUNK;
  data_iter->pagesize = sysconf((int) _SC_PAGESIZE);
  gt_assert(data_iter->start % data_iter->pagesize == 0);
  data_iter->blocksize = data_iter->pagesize * data_iter->pages_per_chunk;
  gt_safe_assign(data_iter->bitseq_per_chunk,
                 (data_iter->blocksize / sizeof (GtBitsequence)));
  data_iter->data = NULL;
  return data_iter;
}
