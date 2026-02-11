symbol_make_alias (symbol *sym, symbol *str, location loc)
{
  if (str->alias)
    complain (&loc, Wother,
              _("symbol %s used more than once as a literal string"), str->tag);
  else if (sym->alias)
    complain (&loc, Wother,
              _("symbol %s given more than one literal string"), sym->tag);
  else
    {
      str->class = token_sym;
      str->user_token_number = sym->user_token_number;
      sym->user_token_number = USER_NUMBER_HAS_STRING_ALIAS;
      str->alias = sym;
      sym->alias = str;
      str->number = sym->number;
      symbol_type_set (str, sym->type_name, loc);
    }
}
