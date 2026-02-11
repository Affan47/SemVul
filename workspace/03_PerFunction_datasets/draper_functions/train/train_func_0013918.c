symbol_precedence_set (symbol *sym, int prec, assoc a, location loc)
{
  if (a != undef_assoc)
    {
      if (sym->prec)
        symbol_redeclaration (sym, assoc_to_string (a), sym->prec_location,
                              loc);
      else
        {
          sym->prec = prec;
          sym->assoc = a;
          sym->prec_location = loc;
        }
    }


  symbol_class_set (sym, token_sym, loc, false);
}
