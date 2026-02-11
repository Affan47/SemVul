builtinTypeInfo (void)
{

  return !mod
    && ((next->isTypeBasic() != NULL && !next->mod)
	|| (next->ty == Tchar && next->mod == MODimmutable)
	|| (next->ty == Tchar && next->mod == MODconst));
}
