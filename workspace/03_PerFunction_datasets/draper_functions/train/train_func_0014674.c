lam_ssi_rpi_usysv_shfree(void *block)
{
  shm_header_t *head;
  shm_header_t *p;

  if (block == 0)
    return;

  shmlock();

  head = (shm_header_t *) block - 1;

  if (*freelist) {


    for (p = poolbase + *freelist;
	 !(head > p && head < poolbase + p->s.ptr);
	 p = poolbase + p->s.ptr) {
      if (p >= poolbase + p->s.ptr
	  && (head > p || head < poolbase + p->s.ptr))


	break;
    }


    *freelist = p - poolbase;

    if (head + head->s.size == poolbase + p->s.ptr) {


      if (p->s.ptr == *freelist) {
	*freelist = head - poolbase;
      }

      if (poolbase + p->s.ptr == p) {
	head->s.ptr = head - poolbase;
      } else {
	head->s.ptr = (poolbase + p->s.ptr)->s.ptr;
      }

      head->s.size += (poolbase + p->s.ptr)->s.size;
    } else {
      head->s.ptr = p->s.ptr;
    }

    if (p + p->s.size == head) {


      p->s.size += head->s.size;
      p->s.ptr = head->s.ptr;
    } else
      p->s.ptr = head - poolbase;
  } else {


    head->s.ptr = head - poolbase;
    *freelist = head - poolbase;
  }

  shmunlock();
}
