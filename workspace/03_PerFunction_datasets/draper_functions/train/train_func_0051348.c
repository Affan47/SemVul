imap_msg_list_to_imap_set(clist * msg_list,
    struct mailimap_set ** result)
{
  struct mailimap_set * imap_set;
  clistiter * cur;
  int previous_valid;
  uint32_t first_seq;
  uint32_t previous;
  int r;
  int res;

  imap_set = mailimap_set_new_empty();
  if (imap_set == NULL) {
    res = MAIL_ERROR_MEMORY;
    goto err;
  }

  cur = clist_begin(msg_list);
  previous_valid = FALSE;
  first_seq = 0;
  previous = 0;
  while (1) {
    uint32_t * pindex;

    if ((cur == NULL) && (previous_valid)) {
      if (first_seq == previous) {
	r = mailimap_set_add_single(imap_set, first_seq);
	if (r != MAILIMAP_NO_ERROR) {
	  res = r;
	  goto free;
	}
      }
      else {
	r = mailimap_set_add_interval(imap_set, first_seq, previous);
	if (r != MAILIMAP_NO_ERROR) {
	  res = r;
	  goto free;
	}
      }
      break;
    }

    pindex = clist_content(cur);

    if (!previous_valid) {
      first_seq = * pindex;
      previous_valid = TRUE;
      previous = * pindex;
      cur = clist_next(cur);
    }
    else {
      if (* pindex != previous + 1) {
	if (first_seq == previous) {
	  r = mailimap_set_add_single(imap_set, first_seq);
	  if (r != MAILIMAP_NO_ERROR) {
	    res = r;
	    goto free;
	  }
	}
	else {
	  r = mailimap_set_add_interval(imap_set, first_seq, previous);
	  if (r != MAILIMAP_NO_ERROR) {
	    res = r;
	    goto free;
	  }
	}
	previous_valid = FALSE;
      }
      else {
	previous = * pindex;
	cur = clist_next(cur);
      }
    }
  }

  * result = imap_set;

  return MAIL_NO_ERROR;

 free:
  mailimap_set_free(imap_set);
 err:
  return res;
}
