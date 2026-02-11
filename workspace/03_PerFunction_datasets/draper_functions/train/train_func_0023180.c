jpeg_build_huffman_index(j_decompress_ptr cinfo, huffman_index *index)
{
    cinfo->tile_decode = TRUE;
    if (cinfo->progressive_mode)
      return jpeg_build_huffman_index_progressive(cinfo, index);
    else
      return jpeg_build_huffman_index_baseline(cinfo, index);
}
