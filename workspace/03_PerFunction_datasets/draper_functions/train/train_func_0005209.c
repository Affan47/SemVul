FinishedRestoringBags( void )
{
  Bag p;

  YoungBags = AllocBags;
  StopBags = AllocBags + WORDS_BAG(AllocSizeBags);
  if (StopBags > EndBags)
    StopBags = EndBags;
  FreeMptrBags = NextMptrRestoring;
  for (p = NextMptrRestoring; p +1 < (Bag)OldBags; p++)
    *(Bag *)p = p+1;
  *p = 0;
  NrLiveBags = NrAllBags;
  SizeLiveBags = SizeAllBags;
  NrDeadBags = 0;
  SizeDeadBags = 0;
  NrHalfDeadBags = 0;
  ChangedBags = 0;
  return;
}
