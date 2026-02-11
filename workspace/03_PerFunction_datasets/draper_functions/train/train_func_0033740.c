layout_add_bands (BonoboDock *dock,
                  BonoboDockLayout *layout,
                  BonoboDockPlacement placement,
                  GList *band_list)
{
  guint band_num;
  GList *lp;

  for (lp = band_list, band_num = 0;
       lp != NULL;
       lp = lp->next, band_num++)
    {
      BonoboDockBand *band;

      band = BONOBO_DOCK_BAND(lp->data);
      bonobo_dock_band_layout_add (band, layout, placement, band_num);
    }
}
