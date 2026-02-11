parse_transactions(std::istream&	   in,
			account_t *	   account,
			entry_base_t&	   entry,
			const std::string& kind,
			unsigned long      beg_pos)
{
  static char line[MAX_LINE + 1];
  bool	      added = false;

  while (! in.eof() && (in.peek() == ' ' || in.peek() == '\t')) {
    in.getline(line, MAX_LINE);
    if (in.eof())
      break;

    int len = std::strlen(line);
    if (line[len - 1] == '\r')
      line[--len] = '\0';

    beg_pos += len + 1;
    linenum++;

    if (line[0] == ' ' || line[0] == '\t') {
      char * p = skip_ws(line);
      if (! *p)
	break;
    }
    if (transaction_t * xact = parse_transaction(line, account)) {
      entry.add_transaction(xact);
      added = true;
    }
  }

  return added;
}
