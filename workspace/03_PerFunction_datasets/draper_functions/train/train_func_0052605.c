free(void* ptr) {

  if(!ptr) {
    return;
  }

  unsigned int hdr_pos = (unsigned)ptr - sizeof(mem_header_t);
  mem_header_t* hdr = (mem_header_t*)hdr_pos;


  if(hdr->magic != MAGIC_USED) {
    return;
  } else {
    unsigned int free_size = hdr->size;
    mem_header_t* next_ptr = hdr->next;
    mem_header_t* prev_ptr = hdr->prev;
    mem_header_t* hdr_ptr  = hdr;

    mem_header_t* adj = hdr->next;

    bool fwd = false;
    bool back = false;


    if(adj && adj->magic == MAGIC_FREE) {
      next_ptr = adj->next;
      prev_ptr = hdr;
      free_size += adj->size + sizeof(mem_header_t);
      fwd = true;
    }


    adj = hdr->prev;
    if(adj && adj->magic == MAGIC_FREE) {

      if(!fwd) {
        next_ptr = hdr;
      }
      prev_ptr = adj->prev;
      hdr_ptr = hdr->prev;
      free_size += adj->size + sizeof(mem_header_t);
      back = true;
    }

    set_free(hdr_ptr, next_ptr, prev_ptr, free_size);
  }
}
