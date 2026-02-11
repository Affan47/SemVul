gt_huffman_decoder_new_from_memory(
                                     GtHuffman *huffman,
                                     GtHuffmanDecoderGetMemFunc mem_func,
                                     void *info,
                                     GtError *err)
{
  GtHuffmanDecoder *huff_decoder = gt_malloc(sizeof (*huff_decoder));

  gt_assert(huffman != NULL);

  huff_decoder->huffman = huffman;
  huff_decoder->cur_node = huff_decoder->huffman->root_huffman_tree;
  huff_decoder->mem_func = mem_func;
  huff_decoder->info = info;
  huff_decoder->cur_bitseq = 0;
  huff_decoder->mem_func_stat =
    huff_decoder->mem_func(&huff_decoder->bitsequence,
                           &huff_decoder->length,
                           &huff_decoder->cur_bit,
                           &huff_decoder->pad_length,
                           huff_decoder->info);
  if (huff_decoder->mem_func_stat == -1) {
    gt_error_set(err, "error calling mem_func");
    return NULL;
  }
  gt_log_log("%lu, %lu, %lu",huff_decoder->length,huff_decoder->cur_bit,
             huff_decoder->pad_length);
  gt_log_log("got new memchunk, returned %d", huff_decoder->mem_func_stat);
  gt_assert(huff_decoder->mem_func_stat == 1);
  return huff_decoder;
}
