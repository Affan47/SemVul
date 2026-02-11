gt_pch_nx_line_maps (void *x_p)
{
  struct line_maps * const x = (struct line_maps *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_9line_maps, gt_ggc_e_9line_maps))
    {
      if ((*x).maps != NULL) {
        size_t i0;
        for (i0 = 0; i0 != (size_t)(((*x)).used); i0++) {
          gt_pch_n_S ((*x).maps[i0].to_file);
        }
        gt_pch_note_object ((*x).maps, x, gt_pch_p_9line_maps, gt_types_enum_last);
      }
    }
}
