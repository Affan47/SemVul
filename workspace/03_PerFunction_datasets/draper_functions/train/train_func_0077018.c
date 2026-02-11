d_print_mod (dpi, mod)
     struct d_print_info *dpi;
     const struct demangle_component *mod;
{
  switch (mod->type)
    {
    case DEMANGLE_COMPONENT_RESTRICT:
    case DEMANGLE_COMPONENT_RESTRICT_THIS:
      d_append_string_constant (dpi, " restrict");
      return;
    case DEMANGLE_COMPONENT_VOLATILE:
    case DEMANGLE_COMPONENT_VOLATILE_THIS:
      d_append_string_constant (dpi, " volatile");
      return;
    case DEMANGLE_COMPONENT_CONST:
    case DEMANGLE_COMPONENT_CONST_THIS:
      d_append_string_constant (dpi, " const");
      return;
    case DEMANGLE_COMPONENT_VENDOR_TYPE_QUAL:
      d_append_char (dpi, ' ');
      d_print_comp (dpi, d_right (mod));
      return;
    case DEMANGLE_COMPONENT_POINTER:

      if ((dpi->options & DMGL_JAVA) == 0)
	d_append_char (dpi, '*');
      return;
    case DEMANGLE_COMPONENT_REFERENCE:
      d_append_char (dpi, '&');
      return;
    case DEMANGLE_COMPONENT_COMPLEX:
      d_append_string_constant (dpi, "complex ");
      return;
    case DEMANGLE_COMPONENT_IMAGINARY:
      d_append_string_constant (dpi, "imaginary ");
      return;
    case DEMANGLE_COMPONENT_PTRMEM_TYPE:
      if (d_last_char (dpi) != '(')
	d_append_char (dpi, ' ');
      d_print_comp (dpi, d_left (mod));
      d_append_string_constant (dpi, "::*");
      return;
    case DEMANGLE_COMPONENT_TYPED_NAME:
      d_print_comp (dpi, d_left (mod));
      return;
    default:


      d_print_comp (dpi, mod);
      return;
    }
}
