meta_rectangle_clamp_to_fit_into_region (const GList         *spanning_rects,
                                         FixedDirections      fixed_directions,
                                         MetaRectangle       *rect,
                                         const MetaRectangle *min_size)
{
  const GList *temp;
  const MetaRectangle *best_rect = NULL;
  int                  best_overlap = 0;


  for (temp = spanning_rects; temp; temp = temp->next)
    {
      MetaRectangle *compare_rect = temp->data;
      int            maximal_overlap_amount_for_compare;


      if ((fixed_directions & FIXED_DIRECTION_X) &&
          (compare_rect->x > rect->x ||
           compare_rect->x + compare_rect->width < rect->x + rect->width))
        continue;


      if ((fixed_directions & FIXED_DIRECTION_Y) &&
          (compare_rect->y > rect->y ||
           compare_rect->y + compare_rect->height < rect->y + rect->height))
        continue;


      if (compare_rect->width  < min_size->width ||
          compare_rect->height < min_size->height)
        continue;


      maximal_overlap_amount_for_compare =
        MIN (rect->width,  compare_rect->width) *
        MIN (rect->height, compare_rect->height);


      if (maximal_overlap_amount_for_compare > best_overlap)
        {
          best_rect    = compare_rect;
          best_overlap = maximal_overlap_amount_for_compare;
        }
    }


  if (best_rect == NULL)
    {
      meta_warning ("No rect whose size to clamp to found!\n");


      if (!(fixed_directions & FIXED_DIRECTION_X))
        rect->width  = min_size->width;
      if (!(fixed_directions & FIXED_DIRECTION_Y))
        rect->height = min_size->height;
    }
  else
    {
      rect->width  = MIN (rect->width,  best_rect->width);
      rect->height = MIN (rect->height, best_rect->height);
    }
}
