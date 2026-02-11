default_elf_select_section_1 (tree decl, int reloc,
			      unsigned HOST_WIDE_INT align, int shlib)
{
  switch (categorize_decl_for_section (decl, reloc, shlib))
    {
    case SECCAT_TEXT:

      abort ();
    case SECCAT_RODATA:
      readonly_data_section ();
      break;
    case SECCAT_RODATA_MERGE_STR:
      mergeable_string_section (decl, align, 0);
      break;
    case SECCAT_RODATA_MERGE_STR_INIT:
      mergeable_string_section (DECL_INITIAL (decl), align, 0);
      break;
    case SECCAT_RODATA_MERGE_CONST:
      mergeable_constant_section (DECL_MODE (decl), align, 0);
      break;
    case SECCAT_SRODATA:
      named_section (NULL_TREE, ".sdata2", reloc);
      break;
    case SECCAT_DATA:
      data_section ();
      break;
    case SECCAT_DATA_REL:
      named_section (NULL_TREE, ".data.rel", reloc);
      break;
    case SECCAT_DATA_REL_LOCAL:
      named_section (NULL_TREE, ".data.rel.local", reloc);
      break;
    case SECCAT_DATA_REL_RO:
      named_section (NULL_TREE, ".data.rel.ro", reloc);
      break;
    case SECCAT_DATA_REL_RO_LOCAL:
      named_section (NULL_TREE, ".data.rel.ro.local", reloc);
      break;
    case SECCAT_SDATA:
      named_section (NULL_TREE, ".sdata", reloc);
      break;
    case SECCAT_TDATA:
      named_section (NULL_TREE, ".tdata", reloc);
      break;
    case SECCAT_BSS:
#ifdef BSS_SECTION_ASM_OP
      bss_section ();
#else
      named_section (NULL_TREE, ".bss", reloc);
#endif
      break;
    case SECCAT_SBSS:
      named_section (NULL_TREE, ".sbss", reloc);
      break;
    case SECCAT_TBSS:
      named_section (NULL_TREE, ".tbss", reloc);
      break;
    default:
      abort ();
    }
}
