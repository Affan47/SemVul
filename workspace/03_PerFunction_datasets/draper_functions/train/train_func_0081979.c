checkInsertPos( QMenu *popup, const QString &str, int &index )
{
  if ( index != -1 )
    return;

  int a = 0;
  const QList<QAction*> actions = popup->actions();
  int b = actions.count();

  while ( a < b )
  {
    int w = ( a + b ) / 2;
    QAction *ac = actions[ w ];
    int j = str.localeAwareCompare( ac->text() );
    if ( j > 0 )
      a = w + 1;
    else
      b = w;
  }

  index = a;

  Q_ASSERT( a == b );
}
