expand_foreach (SExpr& parent_sexpr, SExprIter& parent_pos, unsigned int element_offset, const vector<sstring>& foreach_list, list<SExprIter>& erase)
{
  SExpr& foreach_sexpr = *parent_pos;
  if (CTAGGING(-2,SEXPR_MACROS))
    CL << "About to expand iteration: " << foreach_sexpr << '\n';

  if (!foreach_sexpr[1].is_atom())
    THROWEXPR ("Term following '" << foreach_sexpr[0].atom << "' should be a variable name, but is a list: " << foreach_sexpr);
  const sstring& foreach_var = foreach_sexpr[1].atom;
  if (replace.find (foreach_var) != replace.end())
    THROWEXPR ("Iterator variable '" << foreach_var << "' is already in use: " << foreach_sexpr);

  list<SExpr>::const_iterator
    element_begin = foreach_sexpr.child.begin(),
    element_end = foreach_sexpr.child.end();
  while (element_offset--)
    ++element_begin;
  for_const_contents (vector<sstring>, foreach_list, foreach_val)
    {
      CTAG(0,SEXPR_MACROS SEXPR_EXPAND) << "Expanding " << foreach_var << " to " << *foreach_val << '\n';
      replace[foreach_var] = *foreach_val;
      for_iterator (list<SExpr>::const_iterator, element_iter, element_begin, element_end)
	{
	  SExprIter new_child = parent_sexpr.child.insert (parent_pos, *element_iter);
	  const unsigned int old_erase_sz = erase.size();
	  visit_child (parent_sexpr, new_child, erase);


	  if (old_erase_sz == erase.size())
	    preorder_visit (*new_child);
	}
    }
  replace.erase (foreach_var);
  erase.push_back (parent_pos);
}
