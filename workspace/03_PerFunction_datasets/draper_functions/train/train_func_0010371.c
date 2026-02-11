uniqueify_prefix(const String &base_prefix, RouterT *r)
{

  static HashTable<String, int> *last_uniqueifier;
  if (!last_uniqueifier)
    last_uniqueifier = new HashTable<String, int>(1);
  int count = last_uniqueifier->get(base_prefix);

  while (1) {
    String prefix = base_prefix + "@" + String(count);
    count++;


    int plen = prefix.length();
    for (RouterT::iterator x = r->begin_elements(); x; x++) {
      const String &n = x->name();
      if (n.length() > plen + 1 && n.substring(0, plen) == prefix
	  && n[plen] == '/')
	goto failed;
    }

    last_uniqueifier->set(base_prefix, count);
    return prefix;

   failed: ;
  }
}
