scroll_mouse_motion_handler(SDL_MouseMotionEvent *pMotionEvent, void *pData)
{
  struct hmove *pMotion = (struct hmove *)pData;
  char cBuf[4];

  pMotionEvent->x -= pMotion->pScrollBar->dst->dest_rect.x;

  if (pMotion && pMotionEvent->xrel &&
    (pMotionEvent->x >= pMotion->min) && (pMotionEvent->x <= pMotion->max)) {


    widget_undraw(pMotion->pScrollBar);
    widget_mark_dirty(pMotion->pScrollBar);

    if ((pMotion->pScrollBar->size.x + pMotionEvent->xrel) >
	 (pMotion->max - pMotion->pScrollBar->size.w)) {
      pMotion->pScrollBar->size.x = pMotion->max - pMotion->pScrollBar->size.w;
    } else {
      if ((pMotion->pScrollBar->size.x + pMotionEvent->xrel) < pMotion->min) {
	pMotion->pScrollBar->size.x = pMotion->min;
      } else {
	pMotion->pScrollBar->size.x += pMotionEvent->xrel;
      }
    }

    *(int *)pMotion->pScrollBar->data.ptr =
    		pMotion->base + (pMotion->pScrollBar->size.x - pMotion->min);

    fc_snprintf(cBuf, sizeof(cBuf), "%d", *(int *)pMotion->pScrollBar->data.ptr);
    copy_chars_to_string16(pMotion->pScrollBar->next->string16, cBuf);


    widget_redraw(pMotion->pScrollBar->next);
    widget_mark_dirty(pMotion->pScrollBar->next);


    if (get_wflags(pMotion->pScrollBar) & WF_RESTORE_BACKGROUND) {
      refresh_widget_background(pMotion->pScrollBar);
    }
    widget_redraw(pMotion->pScrollBar);
    widget_mark_dirty(pMotion->pScrollBar);

    flush_dirty();
  }

  return ID_ERROR;
}
