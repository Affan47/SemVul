mark_virtual_phi_result_for_renaming (gimple phi)
{
  if (dump_file && (dump_flags & TDF_DETAILS))
    {
      fprintf (dump_file, "Marking result for renaming : ");
      print_gimple_stmt (dump_file, phi, 0, TDF_SLIM);
      fprintf (dump_file, "\n");
    }

  mark_virtual_operand_for_renaming (gimple_phi_result (phi));
}
