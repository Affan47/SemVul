default_elf_select_rtx_section (mode, x, align)
     enum machine_mode mode;
     rtx x;
     unsigned HOST_WIDE_INT align;
{


  if (flag_pic)
    switch (GET_CODE (x))
      {
      case CONST:
      case SYMBOL_REF:
	named_section (NULL_TREE, ".data.rel.ro", 3);
	return;

      case LABEL_REF:
	named_section (NULL_TREE, ".data.rel.ro.local", 1);
	return;

      default:
	break;
      }

  mergeable_constant_section (mode, align, 0);
}
