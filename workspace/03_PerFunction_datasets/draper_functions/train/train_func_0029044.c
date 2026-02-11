encode_aggregate_within (tree type, int curtype, int format, int left,
			 int right)
{
  tree name;


  int ob_size = obstack_object_size (&util_obstack);
  bool inline_contents = false;
  bool pointed_to = false;

  if (flag_next_runtime)
    {
      if (ob_size > 0  &&  *(obstack_next_free (&util_obstack) - 1) == '^')
	pointed_to = true;

      if ((format == OBJC_ENCODE_INLINE_DEFS || generating_instance_variables)
	  && (!pointed_to || ob_size - curtype == 1
	      || (ob_size - curtype == 2
		  && *(obstack_next_free (&util_obstack) - 2) == 'r')))
	inline_contents = true;
    }
  else
    {


      char c1 = ob_size > 1 ? *(obstack_next_free (&util_obstack) - 2) : 0;
      char c0 = ob_size > 0 ? *(obstack_next_free (&util_obstack) - 1) : 0;

      if (c0 == '^' || (c1 == '^' && c0 == 'r'))
	pointed_to = true;

      if (format == OBJC_ENCODE_INLINE_DEFS || generating_instance_variables)
	{
	  if (!pointed_to)
	    inline_contents = true;
	  else
	    {


	      if ((ob_size - curtype <= 2) && !(c0 == 'r'))
		inline_contents = true;
	    }
	}
    }


  type = TYPE_MAIN_VARIANT (type);
  name = OBJC_TYPE_NAME (type);

  obstack_1grow (&util_obstack, left);


#ifdef OBJCPLUS


  if (name && TREE_CODE (name) == IDENTIFIER_NODE

      && !TYPE_WAS_ANONYMOUS (type))
    obstack_grow (&util_obstack,
		  decl_as_string (type, TFF_DECL_SPECIFIERS | TFF_UNQUALIFIED_NAME),
		  strlen (decl_as_string (type, TFF_DECL_SPECIFIERS | TFF_UNQUALIFIED_NAME)));
#else
  if (name && TREE_CODE (name) == IDENTIFIER_NODE)
    obstack_grow (&util_obstack,
		  IDENTIFIER_POINTER (name),
		  strlen (IDENTIFIER_POINTER (name)));
#endif
  else
    obstack_1grow (&util_obstack, '?');


  if (inline_contents)
    {
      obstack_1grow (&util_obstack, '=');
      encode_aggregate_fields (type, pointed_to, curtype, format);
    }

  obstack_1grow (&util_obstack, right);
}
