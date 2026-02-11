write_handler(const String &in_str, Element *e, void *thunk, ErrorHandler *errh)
{
    ProgressBar *pb = static_cast<ProgressBar *>(e);
    String str = cp_uncomment(in_str);
    switch ((intptr_t)thunk) {
      case H_MARK_STOPPED:
	pb->complete(false);
	return 0;
      case H_MARK_DONE:
	pb->complete(true);
	return 0;
      case H_BANNER:
	pb->_banner = in_str;
	return 0;
      case H_SIZE:
	if (cp_double(str, &pb->_size))
	    return 0;
	else
	    return errh->error("'size' should be double (size value)");
      case H_POSHANDLER:
      case H_SIZEHANDLER: {
	  Vector<String> words;
	  cp_spacevec(str, words);
	  bool is_pos = ((intptr_t)thunk == H_POSHANDLER);
	  int total = (is_pos ? pb->_first_pos_h + words.size() : pb->_es.size() - pb->_first_pos_h + words.size());
	  int offset = (is_pos ? pb->_first_pos_h : 0);

	  Vector<Element*> es(total, 0);
	  Vector<const Handler*> hs(total, 0);

	  for (int i = 0; i < words.size(); i++)
	      if (!cp_handler(words[i], Handler::OP_READ, &es[i+offset], &hs[i+offset], pb, errh))
		  return -1;

	  offset = (is_pos ? 0 : words.size() - pb->_first_pos_h);
	  for (int i = (is_pos ? 0 : pb->_first_pos_h); i < (is_pos ? pb->_first_pos_h : pb->_es.size()); i++)
	      es[i + offset] = pb->_es[i], hs[i + offset] = pb->_hs[i];

	  es.swap(pb->_es);
	  hs.swap(pb->_hs);
	  if (!is_pos) {
	      pb->_have_size = false;
	      pb->_first_pos_h = words.size();
	  }
	  return 0;
      }
      case H_ACTIVE:
	if (cp_bool(str, &pb->_active)) {
	    if (pb->_active && !pb->_timer.scheduled())
		pb->_timer.schedule_now();
	    return 0;
	} else
	    return errh->error("'active' should be bool (active setting)");
      case H_RESET:
	pb->_have_size = false;
	pb->_status = ST_FIRST;
	pb->_active = true;
	pb->_timer.schedule_now();
	return 0;
      default:
	return errh->error("internal");
    }
}
