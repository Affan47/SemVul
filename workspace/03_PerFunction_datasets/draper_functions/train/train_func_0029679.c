finishParseBlock(const QTextBlock &block)
{
  Q_ASSERT(block.isValid());
  int bpos = block.position();
  int cpos = q->e->getBlockIndent(block);


  Ind ind;
  tmpIndents[-9999] = -1;
  tmpOverlays[-9999] = -2;
  QMap<int,int>::const_iterator iti = tmpIndents.end();
  ind.nindent = (--iti).value();
  QMap<int,int>::const_iterator ito = tmpOverlays.end();
  ind.noverlay = (--ito).value();
  iti = tmpIndents.lowerBound(cpos+1);
  ito = tmpOverlays.lowerBound(cpos+1);
  ind.indent = (--iti).value();
  if ((--ito).key() >= iti.key() && ito.value() > -2)
    ind.indent = ito.value();
  indents[bpos] = ind;
  tmpIndents.clear();
  tmpOverlays.clear();
}
