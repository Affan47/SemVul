finalize_literal_type_property (tree t)
{
  tree fn;

  if (cxx_dialect < cxx0x
      || TYPE_HAS_NONTRIVIAL_DESTRUCTOR (t))
    CLASSTYPE_LITERAL_P (t) = false;
  else if (CLASSTYPE_LITERAL_P (t) && !TYPE_HAS_TRIVIAL_DFLT (t)
	   && CLASSTYPE_NON_AGGREGATE (t)
	   && !TYPE_HAS_CONSTEXPR_CTOR (t))
    CLASSTYPE_LITERAL_P (t) = false;

  if (!CLASSTYPE_LITERAL_P (t))
    for (fn = TYPE_METHODS (t); fn; fn = DECL_CHAIN (fn))
      if (DECL_DECLARED_CONSTEXPR_P (fn)
	  && TREE_CODE (fn) != TEMPLATE_DECL
	  && DECL_NONSTATIC_MEMBER_FUNCTION_P (fn)
	  && !DECL_CONSTRUCTOR_P (fn))
	{
	  DECL_DECLARED_CONSTEXPR_P (fn) = false;
	  if (!DECL_GENERATED_P (fn))
	    {
	      error ("enclosing class of constexpr non-static member "
		     "function %q+#D is not a literal type", fn);
	      explain_non_literal_class (t);
	    }
	}
}
