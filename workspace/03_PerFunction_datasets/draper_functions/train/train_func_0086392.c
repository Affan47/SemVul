H5Z_nbit_decompress_one_array(unsigned char *data, size_t data_offset,
           unsigned char *buffer, size_t *j, int *buf_len, const unsigned parms[])
{
   unsigned i, total_size, base_class, base_size, n, begin_index;
   parms_atomic p;

   total_size = parms[parms_index++];
   base_class = parms[parms_index++];

   switch(base_class) {
      case H5Z_NBIT_ATOMIC:
           p.size = parms[parms_index++];
           p.order = parms[parms_index++];
           p.precision = parms[parms_index++];
           p.offset = parms[parms_index++];
           n = total_size/p.size;
           for(i = 0; i < n; i++)
              H5Z_nbit_decompress_one_atomic(data, data_offset + i*p.size,
                                             buffer, j, buf_len, p);
           break;
      case H5Z_NBIT_ARRAY:
           base_size = parms[parms_index];
           n = total_size/base_size;
           begin_index = parms_index;
           for(i = 0; i < n; i++) {
              H5Z_nbit_decompress_one_array(data, data_offset + i*base_size,
                                            buffer, j, buf_len, parms);
              parms_index = begin_index;
           }
           break;
      case H5Z_NBIT_COMPOUND:
           base_size = parms[parms_index];
           n = total_size/base_size;
           begin_index = parms_index;
           for(i = 0; i < n; i++) {
              H5Z_nbit_decompress_one_compound(data, data_offset + i*base_size,
                                               buffer, j, buf_len, parms);
              parms_index = begin_index;
           }
           break;
      case H5Z_NBIT_NOOPTYPE:
           parms_index++;
           H5Z_nbit_decompress_one_nooptype(data, data_offset, buffer, j, buf_len, total_size);
           break;
      default:
          HDassert(0 && "This Should never be executed!");
   }
}
