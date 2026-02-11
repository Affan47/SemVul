set_long_section_mode (bfd *output_bfd, bfd *input_bfd, enum long_section_name_handling style)
{

  if (bfd_get_flavour (output_bfd) == bfd_target_coff_flavour)
    {
      if (style == KEEP
	  && bfd_get_flavour (input_bfd) == bfd_target_coff_flavour)
	style = bfd_coff_long_section_names (input_bfd) ? ENABLE : DISABLE;
      bfd_coff_set_long_section_names (output_bfd, style != DISABLE);
    }
}
