set_offset(hi_ncurses_fpager *pager, off_t offset)
{
  hi_diff_hunk *hunk;
  double ratio;

  if (offset < 0)
  {
    pager->curses->activate_bell = TRUE;
    pager->curses->error = error_messages[error_message_bof];
    return;
  }

  if (offset >= pager->file->size)
  {
    pager->curses->activate_bell = TRUE;
    pager->curses->error = error_messages[error_message_eof];
    return;
  }

  pager->offset = offset;


  if (NULL != pager->linked_pager)
  {
    hunk = hi_diff_get_hunk(pager->diff, pager->file, pager->offset);
    if (hunk != NULL)
    {
      if (pager->diff->src == pager->file)
      {

        if (hunk->type == HI_DIFF_TYPE_DIFF)
        {
          if (hunk->src_end - hunk->src_start == 0)
          {
            ratio = 0.0;
          }
          else
          {
            ratio = (pager->offset - hunk->src_start) / ((double)(hunk->src_end - hunk->src_start));
          }
          pager->linked_pager->offset = hunk->dst_start + (ratio * (hunk->dst_end - hunk->dst_start));
        }
        else
        {
          pager->linked_pager->offset = hunk->dst_start+(pager->offset-hunk->src_start);
        }
      }
      else
      {
        if (hunk->type == HI_DIFF_TYPE_DIFF)
        {
          if (hunk->dst_end - hunk->dst_start == 0)
          {
            ratio = 0.0;
          }
          else
          {
            ratio = (pager->offset - hunk->dst_start) / ((double)(hunk->dst_end - hunk->dst_start));
          }
          pager->linked_pager->offset = hunk->src_start + (ratio * (hunk->src_end - hunk->src_start));
        }
        else
        {
          pager->linked_pager->offset = hunk->src_start+(pager->offset-hunk->dst_start);
        }
      }


      if (pager->linked_pager->offset < 0)
      {
        pager->linked_pager->offset = 0;
      }
      if (pager->linked_pager->offset >= pager->linked_pager->file->size)
      {
        pager->linked_pager->offset = pager->linked_pager->file->size;
      }
    }

  }
}
