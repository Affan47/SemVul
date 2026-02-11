ddjvu_page_get_gamma(ddjvu_page_t *page)
{
  G_TRY
    {
      if (page && page->img)
        return page->img->get_gamma();
    }
  G_CATCH(ex)
    {
      ERROR1(page, ex);
    }
  G_ENDCATCH;
  return 2.2;
}
