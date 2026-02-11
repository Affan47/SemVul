__wcsmbs_clone_conv (struct gconv_fcts *copy)
{
  const struct gconv_fcts *orig;

  orig = get_gconv_fcts (_NL_CURRENT_DATA (LC_CTYPE));


  *copy = *orig;


  if (copy->towc->__shlib_handle != NULL)
    ++copy->towc->__counter;
  if (copy->tomb->__shlib_handle != NULL)
    ++copy->tomb->__counter;
}
