usage() const {

  if (!pd_handlers_sorted) ((orbOptions*)this)->sortHandlers();

  sequenceString_var result(new sequenceString(pd_handlers.size()));

  result->length(pd_handlers.size());

  omnivector<orbOptions::Handler*>::const_iterator i = pd_handlers.begin();
  omnivector<orbOptions::Handler*>::const_iterator last = pd_handlers.end();

  int j = 0;
  for (; i != last; i++) {
    if ((*i)->usage()) {
      result[j] = (*i)->usage();
      j++;
    }
  }
  result->length(j);


  return result._retn();
}
