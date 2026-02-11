output_indirect_string (void **h, void *v ATTRIBUTE_UNUSED)
{
  struct indirect_string_node *node = (struct indirect_string_node *) *h;

  if (node->label && node->refcount)
    {
      switch_to_section (debug_str_section);
      ASM_OUTPUT_LABEL (asm_out_file, node->label);
      assemble_string (node->str, strlen (node->str) + 1);
    }

  return 1;
}
