get_page_for_y(const Glib::RefPtr<const Gtk::PageSetup>& page_setup, Gtk::Unit units, double y)
{
  const double page_height = get_page_height(page_setup, units);
  if(!page_height)
    return 0;

  const double pages = y / (double)page_height;
  double pages_integral = 0;
  modf(pages, &pages_integral);
  return pages_integral;
}
