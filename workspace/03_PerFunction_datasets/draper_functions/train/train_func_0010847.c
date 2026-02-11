scope_name_len(ivl_scope_t net)
{
      unsigned len = 0;

      for (ivl_scope_t cur = net ;  cur ;  cur = cur->parent)
	    len += strlen(cur->name_) + 1;

      return len;
}
