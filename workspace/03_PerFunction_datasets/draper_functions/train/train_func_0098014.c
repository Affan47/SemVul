arm_frame_pointer_required (void)
{
  return (cfun->has_nonlocal_label
          || SUBTARGET_FRAME_POINTER_REQUIRED
          || (TARGET_ARM && TARGET_APCS_FRAME && ! leaf_function_p ()));
}
