get_docked_item_by_name (BonoboDock *dock,
                         const gchar *name,
                         BonoboDockPlacement *placement_return,
                         guint *num_band_return,
                         guint *band_position_return,
                         guint *offset_return)
{
  {
    struct
    {
      GList *band_list;
      BonoboDockPlacement placement;
    }
    areas[] =
    {
      { NULL, BONOBO_DOCK_TOP },
      { NULL, BONOBO_DOCK_BOTTOM },
      { NULL, BONOBO_DOCK_LEFT },
      { NULL, BONOBO_DOCK_RIGHT },
      { NULL, BONOBO_DOCK_FLOATING }
    };
    GList *lp;
    guint i;

    areas[0].band_list = dock->top_bands;
    areas[1].band_list = dock->bottom_bands;
    areas[2].band_list = dock->left_bands;
    areas[3].band_list = dock->right_bands;

    for (i = 0; i < 4; i++)
      {
        guint num_band;

        for (lp = areas[i].band_list, num_band = 0;
             lp != NULL;
             lp = lp->next, num_band++)
          {
            BonoboDockBand *band;
            BonoboDockItem *item;

            band = BONOBO_DOCK_BAND(lp->data);
            item = bonobo_dock_band_get_item_by_name (band,
                                                     name,
                                                     band_position_return,
                                                     offset_return);
            if (item != NULL)
              {
                if (num_band_return != NULL)
                  *num_band_return = num_band;
                if (placement_return != NULL)
                  *placement_return = areas[i].placement;

                return item;
              }
          }
      }
  }

  return NULL;
}
