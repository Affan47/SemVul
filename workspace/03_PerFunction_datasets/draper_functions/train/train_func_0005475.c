append(InheritSpec* is, const char* file, int line)
{
  InheritSpec *i, *last = 0;

  if (is->interface()) {
    for (i=this; i; i = i->next_) {
      last = i;
      if (is->interface() == i->interface()) {
	char* ssn = is->interface()->scopedName()->toString();
	IdlError(file, line,
		 "Cannot specify '%s' as a direct base interface "
		 "more than once", ssn);
	delete [] ssn;
	delete is;
	return;
      }
    }
    last->next_ = is;
  }
}
