unionfind_root ()
{
  web_entry_base *element = this, *element1 = this, *element2;

  while (element->pred ())
    element = element->pred ();
  while (element1->pred ())
    {
      element2 = element1->pred ();
      element1->set_pred (element);
      element1 = element2;
    }
  return element;
}
