alt_size_entry_set_refval_boundaries (AltSizeEntry *gse,
                                       gint           field,
                                       gdouble        lower,
                                       gdouble        upper)
{
  AltSizeEntryField *gsef;

  g_return_if_fail (ALT_IS_SIZE_ENTRY (gse));
  g_return_if_fail ((field >= 0) && (field < gse->number_of_fields));
  g_return_if_fail (lower <= upper);

  gsef = (AltSizeEntryField *) g_slist_nth_data (gse->fields, field);
  gsef->min_refval = lower;
  gsef->max_refval = upper;

  if (gse->show_refval)
    {
      gtk_adjustment_set_lower (GTK_ADJUSTMENT (gsef->refval_adjustment), gsef->min_refval);
      gtk_adjustment_set_upper (GTK_ADJUSTMENT (gsef->refval_adjustment), gsef->max_refval);
    }

  if (gsef->stop_recursion)
    return;

  gsef->stop_recursion++;
  switch (gsef->gse->update_policy)
    {
    case ALT_SIZE_ENTRY_UPDATE_NONE:
      break;

    case ALT_SIZE_ENTRY_UPDATE_SIZE:
      switch (gse->unit)
        {
        case GIMP_UNIT_PIXEL:
          alt_size_entry_set_value_boundaries (gse, field,
                                                gsef->min_refval,
                                                gsef->max_refval);
          break;
        case GIMP_UNIT_PERCENT:
          alt_size_entry_set_value_boundaries (gse, field,
                                                100 * (gsef->min_refval -
                                                       gsef->lower) /
                                                (gsef->upper - gsef->lower),
                                                100 * (gsef->max_refval -
                                                       gsef->lower) /
                                                (gsef->upper - gsef->lower));
          break;
        default:
          alt_size_entry_set_value_boundaries (gse, field,
                                                gsef->min_refval *
                                                gimp_unit_get_factor (gse->unit) /
                                                gsef->resolution,
                                                gsef->max_refval *
                                                gimp_unit_get_factor (gse->unit) /
                                                gsef->resolution);
          break;
        }
      break;

    case ALT_SIZE_ENTRY_UPDATE_RESOLUTION:
      alt_size_entry_set_value_boundaries (gse, field,
                                            gsef->min_refval /
                                            gimp_unit_get_factor (gse->unit),
                                            gsef->max_refval /
                                            gimp_unit_get_factor (gse->unit));
      break;

    default:
      break;
    }
  gsef->stop_recursion--;

  alt_size_entry_set_refval (gse, field, gsef->refval);
}
