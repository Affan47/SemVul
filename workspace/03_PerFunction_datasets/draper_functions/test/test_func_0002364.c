alt_size_entry_set_size (AltSizeEntry *gse,
                          gint           field,
                          gdouble        lower,
                          gdouble        upper)
{
  AltSizeEntryField *gsef;

  g_return_if_fail (ALT_IS_SIZE_ENTRY (gse));
  g_return_if_fail ((field >= 0) && (field < gse->number_of_fields));
  g_return_if_fail (lower <= upper);

  gsef = (AltSizeEntryField*) g_slist_nth_data (gse->fields, field);
  gsef->lower = lower;
  gsef->upper = upper;

  alt_size_entry_set_refval (gse, field, gsef->refval);
}
