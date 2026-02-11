GetHistoBits(int method, int use_palette, int width, int height) {
  const int hist_size = VP8LGetHistogramSize(MAX_COLOR_CACHE_BITS);

  int histo_bits = (use_palette ? 9 : 7) - method;
  while (1) {
    const int huff_image_size = VP8LSubSampleSize(width, histo_bits) *
                                VP8LSubSampleSize(height, histo_bits);
    if ((uint64_t)huff_image_size * hist_size <= MAX_HUFF_IMAGE_SIZE) break;
    ++histo_bits;
  }
  return (histo_bits < MIN_HUFFMAN_BITS) ? MIN_HUFFMAN_BITS :
         (histo_bits > MAX_HUFFMAN_BITS) ? MAX_HUFFMAN_BITS : histo_bits;
}
