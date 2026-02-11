dopage(int pageno)
{
  ddjvu_page_t *page;

  timingdata[0] = ticks();
  if (! (page = ddjvu_page_create_by_pageno(doc, pageno-1)))
    die(i18n("Cannot access page %d."), pageno);
  while (! ddjvu_page_decoding_done(page))
    handle(TRUE);
  if (ddjvu_page_decoding_error(page))
    {
      handle(FALSE);
      fprintf(stderr,"ddjvu: ");
      fprintf(stderr,i18n("Cannot decode page %d."), pageno);
      fprintf(stderr,"\n");
      if (flag_skipcorrupted)
        return;
      else
        exit(10);
    }
  timingdata[1] = ticks();

  if (flag_eachpage)
    {

    }


  openfile(pageno);
  inform(page, pageno);
  render(page, pageno);
  ddjvu_page_release(page);
  closefile(pageno);
}
