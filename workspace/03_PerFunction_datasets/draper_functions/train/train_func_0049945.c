poppler_annot_set_flags (PopplerAnnot *poppler_annot, PopplerAnnotFlag flags)
{
  g_return_if_fail (POPPLER_IS_ANNOT (poppler_annot));

  if (poppler_annot_get_flags (poppler_annot) == flags)
    return;

  poppler_annot->annot->setFlags ((guint) flags);
}
