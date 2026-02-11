loadMimeTypes( const QStringList &_selectedMimeTypes )
{
  QStringList selMimeTypes;

  if ( !_selectedMimeTypes.isEmpty() )
    selMimeTypes = _selectedMimeTypes;
  else
    selMimeTypes = q->mimeTypes();

  mimeTypeTree->clear();

  QMap<QString, QTreeWidgetItem*> groupItems;
  const KMimeType::List mimetypes = KMimeType::allMimeTypes();

  bool agroupisopen = false;
  QTreeWidgetItem *idefault = 0;
  QTreeWidgetItem *firstChecked = 0;

  foreach (const KMimeType::Ptr& mt, mimetypes)
  {
    const QString mimetype = mt->name();
    const int index = mimetype.indexOf('/');
    const QString maj = mimetype.left(index);

    if ( !groups.isEmpty() && !groups.contains( maj ) )
      continue;

    QTreeWidgetItem *groupItem;
    QMap<QString,QTreeWidgetItem*>::Iterator mit = groupItems.find( maj );
    if ( mit == groupItems.end() )
    {
        groupItem = new QTreeWidgetItem( mimeTypeTree, QStringList(maj) );
        groupItems.insert( maj, groupItem );
        if ( maj == defaultgroup )
            idefault = groupItem;
    }
    else
        groupItem = mit.value();

    const QString min = mimetype.mid(index+1);
    QTreeWidgetItem *item = new QTreeWidgetItem( groupItem, QStringList(min) );
    item->setIcon( 0, KIcon( mt->iconName() ) );

    int cl = 1;

    if ( visuals & KMimeTypeChooser::Comments )
    {
      item->setText( cl, mt->comment() );
      cl++;
    }

    if ( visuals & KMimeTypeChooser::Patterns )
      item->setText( cl, mt->patterns().join("; ") );

    if ( selMimeTypes.contains(mimetype) ) {
      item->setCheckState( 0, Qt::Checked );
      groupItem->setExpanded( true );
      agroupisopen = true;
      if ( !firstChecked )
        firstChecked = item;
    } else {
      item->setCheckState( 0, Qt::Unchecked );
    }
  }

  if ( firstChecked )
    mimeTypeTree->scrollToItem( firstChecked );

  if ( !agroupisopen && idefault )
  {
    idefault->setExpanded( true );
    mimeTypeTree->scrollToItem( idefault );
  }
  mimeTypeTree->resizeColumnToContents(1);
}
