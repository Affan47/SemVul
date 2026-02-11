move_to_next_diff(hi_ncurses_fpager *pager, int times, gboolean bigdiff)
{
  hi_diff_hunk *hunk = NULL, *hunk2 = NULL;
  int i=0;
  int times_abs = abs(times);
  gboolean forwards= FALSE;

  if (pager->diff == NULL)
  {
    return;
  }

  if (times_abs == times)
    forwards = TRUE;

  while (i < times_abs)
  {
    hunk = hi_diff_get_hunk(pager->diff, pager->file, pager->offset);
    if (NULL != hunk)
    {
      if (forwards)
      {
        if (pager->file == pager->diff->src)
        {
          set_offset(pager, hunk->src_end+1);
        }
        if (pager->file == pager->diff->dst)
        {
          set_offset(pager, hunk->dst_end+1);
        }
      }
      else
      {
        if (pager->file == pager->diff->src)
        {
          set_offset(pager, hunk->src_start-1);
        }
        if (pager->file == pager->diff->dst)
        {
          set_offset(pager, hunk->dst_start-1);
        }
      }
      if (bigdiff == TRUE)
      {
        hunk2 = hi_diff_get_hunk(pager->diff, pager->file, pager->offset);
        if (NULL != hunk2)
        {
          if (hunk2 == hunk)
          {
            break;
          }
          if ((hunk2->type != HI_DIFF_TYPE_DIFF) ||
              ((hunk2->src_end - hunk2->src_start < pager->curses->big_hunk_size) ||
              (hunk2->dst_end - hunk2->dst_start < pager->curses->big_hunk_size)))
          {
            continue;
          }
        }

      }
    }
    else
    {
      break;
    }
    i++;
  }


  if ((bigdiff == TRUE) && (hunk != hunk2))
  {
    hunk = hi_diff_get_hunk(pager->diff, pager->file, pager->offset);
    if (hunk != NULL)
    {
      if (pager->file == pager->diff->src)
      {
        set_offset(pager, hunk->src_start);
      }
      if (pager->file == pager->diff->dst)
      {
        set_offset(pager, hunk->dst_start);
      }
    }
  }
}
