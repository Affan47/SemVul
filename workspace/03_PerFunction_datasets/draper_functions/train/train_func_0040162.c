add_pubtype (tree decl, dw_die_ref die)
{
  pubname_entry e;

  if (!targetm.want_debug_pub_sections)
    return;

  e.name = NULL;
  if ((TREE_PUBLIC (decl)
       || is_cu_die (die->die_parent))
      && (die->die_tag == DW_TAG_typedef || COMPLETE_TYPE_P (decl)))
    {
      e.die = die;
      if (TYPE_P (decl))
	{
	  if (TYPE_NAME (decl))
	    {
	      if (TREE_CODE (TYPE_NAME (decl)) == IDENTIFIER_NODE)
		e.name = IDENTIFIER_POINTER (TYPE_NAME (decl));
	      else if (TREE_CODE (TYPE_NAME (decl)) == TYPE_DECL
		       && DECL_NAME (TYPE_NAME (decl)))
		e.name = IDENTIFIER_POINTER (DECL_NAME (TYPE_NAME (decl)));
	      else
	       e.name = xstrdup ((const char *) get_AT_string (die, DW_AT_name));
	    }
	}
      else
	{
	  e.name = dwarf2_name (decl, 1);
	  if (e.name)
	    e.name = xstrdup (e.name);
	}


      if (e.name && e.name[0] != '\0')
	VEC_safe_push (pubname_entry, gc, pubtype_table, &e);
    }
}
