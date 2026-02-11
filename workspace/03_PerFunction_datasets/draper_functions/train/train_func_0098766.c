Collect(const WordReference& wordRef)
{
  WordCursor *search = Cursor(wordRef.Key(), HTDIG_WORDLIST_COLLECTOR);
  if(search->Walk() != OK) return 0;
  List* result = search->GetResults();
  delete search;
  return result;
}
