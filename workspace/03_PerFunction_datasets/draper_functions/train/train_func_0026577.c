updateSearch( const QString &s )
{
  Q3IconView *iv = d->iconView;
  if( ! iv )
    return;

  QString search = d->search = s.isNull() ? text() : s;

  QIconViewItemList *hi = &(d->hiddenItems);

  Q3IconViewItem *currentItem = iv->currentItem();

  Q3IconViewItem *item = NULL;


  Q3IconViewItem *i = iv->firstItem();
  while ( i != NULL )
    {
      item = i;
      i = i->nextItem();
      if ( ! itemMatches( item, search ) )
	{
	  hideItem( item );

	  if ( item == currentItem )
	    currentItem = NULL;
	}
    }


    QIconViewItemList::iterator it = hi->begin();
    while ( it != hi->end() )
      {
	item = *it;
	++it;
	if ( itemMatches( item, search ) )
	  showItem( item );
      }

    iv->sort();

    if ( currentItem != NULL )
      iv->ensureItemVisible( currentItem );
}
