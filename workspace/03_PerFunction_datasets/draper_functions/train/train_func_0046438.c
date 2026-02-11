block_label (basic_block block)
{
  if (block == EXIT_BLOCK_PTR)
    return NULL_RTX;

  if (GET_CODE (BB_HEAD (block)) != CODE_LABEL)
    {
      BB_HEAD (block) = emit_label_before (gen_label_rtx (), BB_HEAD (block));
    }

  return BB_HEAD (block);
}
