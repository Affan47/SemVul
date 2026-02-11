gt_bed_to_gff3_arguments_delete(void *tool_arguments)
{
  BEDToGFF3Arguments *arguments = tool_arguments;
  if (!arguments) return;
  gt_file_delete(arguments->outfp);
  gt_output_file_info_delete(arguments->ofi);
  gt_str_delete(arguments->block_type);
  gt_str_delete(arguments->thick_feature_type);
  gt_str_delete(arguments->feature_type);
  gt_free(arguments);
}
