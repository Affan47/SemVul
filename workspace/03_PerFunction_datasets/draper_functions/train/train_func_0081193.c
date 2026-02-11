poppler_page_get_text_attributes (PopplerPage *page)
{
  TextPage *text;
  TextWordList *wordlist;
  PopplerTextAttributes *attrs = NULL;
  PopplerTextAttributes *previous = NULL;
  gint i, offset = 0;
  GList *attributes = NULL;

  g_return_val_if_fail (POPPLER_IS_PAGE (page), NULL);

  text = poppler_page_get_text_page (page);
  wordlist = text->makeWordList (gFalse);

  if (wordlist->getLength () <= 0)
    {
      delete wordlist;
      return NULL;
    }


  for (i = 0; i < wordlist->getLength (); i++)
    {
      TextWord *word = wordlist->get (i);


      if (i > 0 && word_text_attributes_equal (word, wordlist->get (i - 1))) {
        attrs = previous;
      } else {
        attrs = poppler_text_attributes_new_from_word (word);
        attrs->start_index = offset;
        if (previous)
          previous->end_index--;
        previous = attrs;
        attributes = g_list_prepend (attributes, attrs);
      }
      offset += word->getLength () + 1;
      attrs->end_index = offset;
    }
  if (attrs)
    attrs->end_index--;

  delete wordlist;

  return g_list_reverse(attributes);
}
