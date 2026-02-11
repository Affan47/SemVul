gt_pch_n_P11cgraph_node4htab (void *x_p)
{
  struct htab * const x = (struct htab *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_P11cgraph_node4htab, gt_types_enum_last))
    {
      if ((*x).entries != NULL) {
        size_t i0;
        for (i0 = 0; i0 != (size_t)(((*x)).size); i0++) {
          gt_pch_n_11cgraph_node ((*x).entries[i0]);
        }
        gt_pch_note_object ((*x).entries, x, gt_pch_p_P11cgraph_node4htab, gt_types_enum_last);
      }
    }
}
