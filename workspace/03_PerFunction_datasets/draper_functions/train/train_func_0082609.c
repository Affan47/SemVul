funnyWord( const QString & word )


{
  QString qs;
  for( int i=0; i<word.size(); i++ )
  {
    if (word [i]=='+')
      continue;
    if (word [i]=='-')
    {
      QString shorty;
      int j, k;

      for( j = i+1; j < word.size() && word[j] != '+' && word[j] != '-'; j++ )
        shorty += word[j];

      i = j-1;

      if ( !( k = qs.lastIndexOf(shorty) ) || k != -1 )
        qs.remove( k, shorty.length() );
      else
      {
        qs += '-';
        qs += shorty;
      }
    }
    else
      qs += word[i];
  }

  return qs;
}
