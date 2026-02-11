dump_access (FILE *f, struct access *access, bool grp)
{
  fprintf (f, "access { ");
  fprintf (f, "base = (%d)'", DECL_UID (access->base));
  print_generic_expr (f, access->base, 0);
  fprintf (f, "', offset = " HOST_WIDE_INT_PRINT_DEC, access->offset);
  fprintf (f, ", size = " HOST_WIDE_INT_PRINT_DEC, access->size);
  fprintf (f, ", expr = ");
  print_generic_expr (f, access->expr, 0);
  fprintf (f, ", type = ");
  print_generic_expr (f, access->type, 0);
  if (grp)
    fprintf (f, ", total_scalarization = %d, grp_read = %d, grp_write = %d, "
	     "grp_assignment_read = %d, grp_assignment_write = %d, "
	     "grp_scalar_read = %d, grp_scalar_write = %d, "
	     "grp_hint = %d, grp_covered = %d, "
	     "grp_unscalarizable_region = %d, grp_unscalarized_data = %d, "
	     "grp_partial_lhs = %d, grp_to_be_replaced = %d, "
	     "grp_maybe_modified = %d, "
	     "grp_not_necessarilly_dereferenced = %d\n",
	     access->total_scalarization, access->grp_read, access->grp_write,
	     access->grp_assignment_read, access->grp_assignment_write,
	     access->grp_scalar_read, access->grp_scalar_write,
	     access->grp_hint, access->grp_covered,
	     access->grp_unscalarizable_region, access->grp_unscalarized_data,
	     access->grp_partial_lhs, access->grp_to_be_replaced,
	     access->grp_maybe_modified,
	     access->grp_not_necessarilly_dereferenced);
  else
    fprintf (f, ", write = %d, total_scalarization = %d, "
	     "grp_partial_lhs = %d\n",
	     access->write, access->total_scalarization,
	     access->grp_partial_lhs);
}
