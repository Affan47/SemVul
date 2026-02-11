pp_base_destroy_prefix (pretty_printer *pp)
{
  if (pp->prefix != NULL)
    {
      free (CONST_CAST (char *, pp->prefix));
      pp->prefix = NULL;
    }
}
