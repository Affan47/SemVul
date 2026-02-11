_poppler_page_render (PopplerPage      *page,
		      cairo_t          *cairo,
		      GBool             printing,
                      PopplerPrintFlags print_flags)
{
  CairoOutputDev *output_dev;

  g_return_if_fail (POPPLER_IS_PAGE (page));

  output_dev = page->document->output_dev;
  output_dev->setCairo (cairo);
  output_dev->setPrinting (printing);

  if (!printing)
    output_dev->setTextPage (page->text);


  cairo_save (cairo);
  page->page->displaySlice(output_dev,
			   72.0, 72.0, 0,
			   gFalse,
			   gTrue,
			   -1, -1,
			   -1, -1,
			   printing,
			   page->document->doc->getCatalog (),
			   NULL, NULL,
			   printing ? poppler_print_annot_cb : NULL,
                           printing ? GINT_TO_POINTER ((gint)print_flags) : NULL);
  cairo_restore (cairo);

  output_dev->setCairo (NULL);
  output_dev->setTextPage (NULL);
}
