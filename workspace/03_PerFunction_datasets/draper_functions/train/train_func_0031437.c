warn_deprecated_use (tree node, tree attr)
{
  const char *msg;

  if (node == 0 || !warn_deprecated_decl)
    return;

  if (!attr)
    {
      if (DECL_P (node))
	attr = DECL_ATTRIBUTES (node);
      else if (TYPE_P (node))
	{
	  tree decl = TYPE_STUB_DECL (node);
	  if (decl)
	    attr = lookup_attribute ("deprecated",
				     TYPE_ATTRIBUTES (TREE_TYPE (decl)));
	}
    }

  if (attr)
    attr = lookup_attribute ("deprecated", attr);

  if (attr)
    msg = TREE_STRING_POINTER (TREE_VALUE (TREE_VALUE (attr)));
  else
    msg = NULL;

  if (DECL_P (node))
    {
      expanded_location xloc = expand_location (DECL_SOURCE_LOCATION (node));
      if (msg)
	warning (OPT_Wdeprecated_declarations,
		 "%qD is deprecated (declared at %s:%d): %s",
		 node, xloc.file, xloc.line, msg);
      else
	warning (OPT_Wdeprecated_declarations,
		 "%qD is deprecated (declared at %s:%d)",
		 node, xloc.file, xloc.line);
    }
  else if (TYPE_P (node))
    {
      tree what = NULL_TREE;
      tree decl = TYPE_STUB_DECL (node);

      if (TYPE_NAME (node))
	{
	  if (TREE_CODE (TYPE_NAME (node)) == IDENTIFIER_NODE)
	    what = TYPE_NAME (node);
	  else if (TREE_CODE (TYPE_NAME (node)) == TYPE_DECL
		   && DECL_NAME (TYPE_NAME (node)))
	    what = DECL_NAME (TYPE_NAME (node));
	}

      if (decl)
	{
	  expanded_location xloc
	    = expand_location (DECL_SOURCE_LOCATION (decl));
	  if (what)
	    {
	      if (msg)
		warning (OPT_Wdeprecated_declarations,
			 "%qE is deprecated (declared at %s:%d): %s",
			 what, xloc.file, xloc.line, msg);
	      else
		warning (OPT_Wdeprecated_declarations,
			 "%qE is deprecated (declared at %s:%d)", what,
			 xloc.file, xloc.line);
	    }
	  else
	    {
	      if (msg)
		warning (OPT_Wdeprecated_declarations,
			 "type is deprecated (declared at %s:%d): %s",
			 xloc.file, xloc.line, msg);
	      else
		warning (OPT_Wdeprecated_declarations,
			 "type is deprecated (declared at %s:%d)",
			 xloc.file, xloc.line);
	    }
	}
      else
	{
	  if (what)
	    {
	      if (msg)
		warning (OPT_Wdeprecated_declarations, "%qE is deprecated: %s",
			 what, msg);
	      else
		warning (OPT_Wdeprecated_declarations, "%qE is deprecated", what);
	    }
	  else
	    {
	      if (msg)
		warning (OPT_Wdeprecated_declarations, "type is deprecated: %s",
			 msg);
	      else
		warning (OPT_Wdeprecated_declarations, "type is deprecated");
	    }
	}
    }
}
