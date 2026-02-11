print_instantiation_full_context (diagnostic_context *context)
{
  struct tinst_level *p = current_instantiation ();
  location_t location = input_location;

  if (p)
    {
      pp_verbatim (context->printer,
		   TREE_CODE (p->decl) == TREE_LIST
		   ? _("%s: In substitution of %qS:\n")
		   : _("%s: In instantiation of %q#D:\n"),
		   LOCATION_FILE (location),
		   p->decl);

      location = p->locus;
      p = p->next;
    }

  print_instantiation_partial_context (context, p, location);
}
