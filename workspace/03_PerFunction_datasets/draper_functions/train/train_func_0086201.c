setItemDelegate( QAbstractItemDelegate *delegate )
{
    Q_D(KPageView);
  if ( d->view )
    d->view->setItemDelegate( delegate );
}
