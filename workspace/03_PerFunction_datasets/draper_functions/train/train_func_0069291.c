prepareTextSearch(const QString &text, Page::SearchMode caseSensitive, Page::Rotation rotate, GBool *sCase, QVector<Unicode> *u)
{
  const QChar * str = text.unicode();
  const int len = text.length();
  u->resize(len);
  for (int i = 0; i < len; ++i) (*u)[i] = str[i].unicode();

  if (caseSensitive == Page::CaseSensitive) *sCase = gTrue;
  else *sCase = gFalse;

  const int rotation = (int)rotate * 90;


  TextOutputDev td(NULL, gTrue, 0, gFalse, gFalse);
  parentDoc->doc->displayPage( &td, index + 1, 72, 72, rotation, false, true, false,
    NULL, NULL, NULL, NULL, gTrue);
  TextPage *textPage=td.takeText();

  return textPage;
}
