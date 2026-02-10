find_free_size(const unsigned int size,
					skip_alloc_t *update_p)
{
  int		level_c, cmp;
  skip_alloc_t 	*slot_p, *found_p = NULL, *next_p;


  level_c = MAX_SKIP_LEVEL - 1;
  slot_p = skip_free_list;


  while (1) {


    next_p = slot_p->sa_next_p[level_c];


    if (next_p == NULL
	|| next_p == found_p) {

    }
    else {
      cmp = next_p->sa_total_size - size;
      if (cmp < 0) {

	slot_p = next_p;
	continue;
      }
      else if (cmp == 0) {


	found_p = next_p;
      }
    }


    update_p->sa_next_p[level_c] = slot_p;
    if (level_c == 0) {
      break;
    }
    level_c--;
  }


  if (found_p != NULL && (! BIT_IS_SET(found_p->sa_flags, ALLOC_FLAG_FREE))) {

    dmalloc_errno = ERROR_ADDRESS_LIST;
    dmalloc_error("find_free_size");
    return NULL;
  }

  return found_p;
}
