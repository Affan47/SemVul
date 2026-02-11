aarch64_mangle_type (const_tree type)
{


  if (lang_hooks.types_compatible_p (CONST_CAST_TREE (type), va_list_type))
    return "St9__va_list";


  if (TREE_CODE (type) == VECTOR_TYPE)
    {
      aarch64_simd_mangle_map_entry *pos = aarch64_simd_mangle_map;

      while (pos->mode != VOIDmode)
	{
	  tree elt_type = TREE_TYPE (type);

	  if (pos->mode == TYPE_MODE (type)
	      && TREE_CODE (TYPE_NAME (elt_type)) == TYPE_DECL
	      && !strcmp (IDENTIFIER_POINTER (DECL_NAME (TYPE_NAME (elt_type))),
			  pos->element_type_name))
	    return pos->mangled_name;

	  pos++;
	}
    }


  return NULL;
}
