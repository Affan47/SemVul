gt_bitinstream_new(const char* path,
                                  size_t offset,
                                  unsigned long pages_to_map)
{
  GtBitInStream *bitstream = gt_malloc(sizeof (*bitstream));

  bitstream->pagesize =sysconf((int) _SC_PAGESIZE);
  bitstream->last_chunk = false;
  gt_safe_assign(bitstream->filesize, gt_file_estimate_size(path));
  bitstream->path = gt_cstr_dup(path);
  bitstream->pages_to_map = pages_to_map;

  if ((unsigned long) bitstream->filesize <
      (bitstream->pages_to_map * bitstream->pagesize))
    bitstream->pages_to_map =
      (unsigned long) ((bitstream->filesize / bitstream->pagesize) + 1);

  bitstream->bitseqbuffer = NULL;
  bitstream->read_bits = 0;
  gt_bitinstream_reinit(bitstream,
                        offset);

  bitstream->bufferlength = (bitstream->pages_to_map * bitstream->pagesize) /
                            sizeof (*bitstream->bitseqbuffer);
  return bitstream;
}
