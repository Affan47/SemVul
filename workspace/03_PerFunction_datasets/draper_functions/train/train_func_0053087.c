gth_input_delete_complete(GthInput *input)
{
  if (!input) return;
  gth_input_delete_current(input);
  gt_str_delete(input->bssmfile);
  gt_str_delete(input->proteinsmap);
  gt_score_matrix_delete(input->score_matrix);
  gt_alphabet_delete(input->score_matrix_alpha);
  gt_array_delete(input->alphatypes);
  gt_str_array_delete(input->referencefiles);
  gt_str_array_delete(input->genomicfiles);
  gt_free(input);
}
