cbf_decompress_byte_offset(void         *destination,
                                size_t        elsize,
                                int           elsign,
                                size_t        nelem,
                                size_t       *nelem_read,
                                size_t        compressedsize,
                                unsigned int  compression,
                                int           data_bits,
                                int           data_sign,
                                cbf_file     *file,
                                int           realarray,
                                const char   *byteorder,
                                size_t        dimover,
                                size_t        dimfast,
                                size_t        dimmid,
                                size_t        dimslow,
                                size_t        padding)
{


  if (file->bits[0] != 0 || elsize > sizeof(CBF_ull_type) || CHAR_BIT != 8 ||
      ~0 != -1 || (elsize != 1 && elsize != 2 && elsize != 4 && elsize !=8 ) ) {
    return cbf_decompress_byte_offset_slow(destination, elsize, elsign,
        nelem, nelem_read, compressedsize, compression, data_bits, data_sign,
        file, realarray, byteorder, dimover, dimfast, dimmid, dimslow, padding);
  }

  return cbf_decompress_byte_offset_fast(destination, elsize, elsign,
      nelem, nelem_read, compressedsize, compression, data_bits, data_sign,
      file, realarray, byteorder, dimover, dimfast, dimmid, dimslow, padding);
}
