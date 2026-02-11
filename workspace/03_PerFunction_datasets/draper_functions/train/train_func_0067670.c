expand_eh_region_end_must_not_throw (tree failure)
{
  struct eh_region *region;
  rtx around_label;

  if (! doing_eh (0))
    return;

  region = expand_eh_region_end ();
  region->type = ERT_MUST_NOT_THROW;
  region->label = gen_label_rtx ();


  around_label = gen_label_rtx ();
  emit_jump (around_label);

  emit_label (region->label);
  expand_expr (failure, const0_rtx, VOIDmode, EXPAND_NORMAL);

  emit_label (around_label);
}
