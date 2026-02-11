add_define_subst_attr (const char **attr_operands, rtx *queue)
{
  rtx return_rtx;
  int i;

  return_rtx = rtx_alloc (DEFINE_SUBST_ATTR);
  PUT_CODE (return_rtx, DEFINE_SUBST_ATTR);

  for (i = 0; i < 4; i++)
    XSTR (return_rtx, i) = xstrdup (attr_operands[i]);

  XEXP (*queue, 0) = return_rtx;
  XEXP (*queue, 1) = NULL_RTX;
}
