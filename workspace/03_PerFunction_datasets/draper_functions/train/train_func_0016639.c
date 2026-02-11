enter_file_scope ()
{
  if (!identtab_loc)
    identtab_loc = allocate_loc_tables (identtab_loc);

  if (identtab_loc->file_scope != spf[s].name)
    identtab_loc->file_scope = spf[s].name;
}
