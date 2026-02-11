checkWord2(  )
{
  QString word;
  QString line;
  line = d->convertQByteArray( proc->readLine() );


  QByteArray data;
  while (proc->readLine( data.data(), data.count() ) != -1 ) ;
  NOOUTPUT(checkWord2);

  bool mistake = ( parseOneResponse(line, word, sugg) == MISTAKE );
  if ( mistake && usedialog )
  {
    cwword = word;
    dialog( word, sugg, SLOT(checkWord3()) );
    d->checkNextTimer->setInterval(0);
    d->checkNextTimer->setSingleShot(true);
    d->checkNextTimer->start();
    return;
  }
  else if( mistake )
  {
    emit misspelling( word, sugg, lastpos );
  }


  emit corrected( word, word, 0L );
  d->checkNextTimer->setInterval(0);
  d->checkNextTimer->setSingleShot(true);
  d->checkNextTimer->start();
}
