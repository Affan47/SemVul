ReduceImageColors(const Image *image,CubeInfo *cube_info)
{
#define ReduceImageTag  "Reduce/Image"

  MagickBooleanType
    proceed;

  MagickOffsetType
    offset;

  size_t
    span;

  cube_info->next_threshold=0.0;
  for (span=cube_info->colors; cube_info->colors > cube_info->maximum_colors; )
  {
    cube_info->pruning_threshold=cube_info->next_threshold;
    cube_info->next_threshold=cube_info->root->quantize_error-1;
    cube_info->colors=0;
    Reduce(image,cube_info,cube_info->root);
    offset=(MagickOffsetType) span-cube_info->colors;
    proceed=SetImageProgress(image,ReduceImageTag,offset,span-
      cube_info->maximum_colors+1);
    if (proceed == MagickFalse)
      break;
  }
}
