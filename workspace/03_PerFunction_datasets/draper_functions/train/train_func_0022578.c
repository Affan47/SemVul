warn_ref_binding (tree reftype, tree intype, tree decl)
{
  tree ttl = TREE_TYPE (reftype);

  if (!CP_TYPE_CONST_NON_VOLATILE_P (ttl))
    {
      const char *msg;

      if (CP_TYPE_VOLATILE_P (ttl) && decl)
	msg = G_("initialization of volatile reference type %q#T from "
	         "rvalue of type %qT");
      else if (CP_TYPE_VOLATILE_P (ttl))
	msg = G_("conversion to volatile reference type %q#T "
	         "from rvalue of type %qT");
      else if (decl)
	msg = G_("initialization of non-const reference type %q#T from "
	         "rvalue of type %qT");
      else
	msg = G_("conversion to non-const reference type %q#T from "
	         "rvalue of type %qT");

      permerror (input_location, msg, reftype, intype);
    }
}
