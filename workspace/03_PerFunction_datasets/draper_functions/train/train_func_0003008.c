jerasure_bitmatrix_dotprod(int k, int w, int *bitmatrix_row,
                             int *src_ids, int dest_id,
                             char **data_ptrs, char **coding_ptrs, int size, int packetsize)
{
  int j, sindex, pstarted, index, x, y;
  char *dptr, *pptr, *bdptr, *bpptr;

  if (size%(w*packetsize) != 0) {
    fprintf(stderr, "jerasure_bitmatrix_dotprod - size%c(w*packetsize)) must = 0\n", '%');
    exit(1);
  }

  bpptr = (dest_id < k) ? data_ptrs[dest_id] : coding_ptrs[dest_id-k];

  for (sindex = 0; sindex < size; sindex += (packetsize*w)) {
    index = 0;
    for (j = 0; j < w; j++) {
      pstarted = 0;
      pptr = bpptr + sindex + j*packetsize;
      for (x = 0; x < k; x++) {
        if (src_ids == NULL) {
          bdptr = data_ptrs[x];
        } else if (src_ids[x] < k) {
          bdptr = data_ptrs[src_ids[x]];
        } else {
          bdptr = coding_ptrs[src_ids[x]-k];
        }
        for (y = 0; y < w; y++) {
          if (bitmatrix_row[index]) {
            dptr = bdptr + sindex + y*packetsize;
            if (!pstarted) {
              memcpy(pptr, dptr, packetsize);
              jerasure_total_memcpy_bytes += packetsize;
              pstarted = 1;
            } else {
              galois_region_xor(dptr, pptr, packetsize);
              jerasure_total_xor_bytes += packetsize;
            }
          }
          index++;
        }
      }
    }
  }
}
