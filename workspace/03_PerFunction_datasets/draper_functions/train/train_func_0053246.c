exit_scope ()
{
  clear_hash_tab ();
  clear_tag_tab ();
  scope_level ? scope_level-- : 0;
}
