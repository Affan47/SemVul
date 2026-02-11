set_cma_hscrollbars(void)
{
  struct widget *pBuf;
  char cBuf[4];

  if (!pCma) {
    return;
  }


  pBuf = pCma->pDlg->pEndWidgetList->prev;
  output_type_iterate(i) {

    pBuf = pBuf->prev;
    fc_snprintf(cBuf, sizeof(cBuf), "%d", *(int *)pBuf->prev->data.ptr);
    copy_chars_to_string16(pBuf->string16, cBuf);


    pBuf = pBuf->prev;
    pBuf->size.x = pBuf->next->size.x
    	+ pBuf->next->size.w + adj_size(5) + adj_size(20) + *(int *)pBuf->data.ptr;


    pBuf = pBuf->prev;
    fc_snprintf(cBuf, sizeof(cBuf), "%d", *(int *)pBuf->prev->data.ptr);
    copy_chars_to_string16(pBuf->string16, cBuf);


    pBuf = pBuf->prev;
    pBuf->size.x = pBuf->next->size.x
    		+ pBuf->next->size.w + adj_size(5) + *(int *)pBuf->data.ptr - 1;

  } output_type_iterate_end;


  pBuf = pBuf->prev;
  fc_snprintf(cBuf, sizeof(cBuf), "%d", *(int *)pBuf->prev->data.ptr);
  copy_chars_to_string16(pBuf->string16, cBuf);


  pBuf = pBuf->prev;
  pBuf->size.x = pBuf->next->size.x
    		+ pBuf->next->size.w + adj_size(5) + *(int *)pBuf->data.ptr - 1;

}
