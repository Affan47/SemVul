s_match(s_expression *top, unsigned n, s_pattern *pattern, bool partial)
{
   s_list *list = SX_AS_LIST(top);
   if (list == NULL)
      return false;

   unsigned i = 0;
   foreach_iter(exec_list_iterator, it, list->subexpressions) {
      if (i >= n)
	 return partial;

      s_expression *expr = (s_expression *) it.get();
      if (expr == NULL || !pattern[i].match(expr))
	 return false;

      i++;
   }

   if (i < n)
      return false;

   return true;
}
