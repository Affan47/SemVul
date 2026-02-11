basic()
{

  Page *page = new Page;
  page->addLayer("alpha");
  page->insertView(0, "alpha");
  page->setVisible(0, "alpha", true);
  return page;
}
