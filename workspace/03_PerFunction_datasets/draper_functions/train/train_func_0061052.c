rowsInserted( const QModelIndex &, int , int  )
  {
    Q_Q(KViewStateSaver);
    processPendingChanges();

    if ( !hasPendingChanges() )
    {
      q->disconnect( getModel(), SIGNAL(rowsInserted(QModelIndex,int,int)),
          q, SLOT(rowsInserted(QModelIndex,int,int)) );
      q->deleteLater();
    }
  }
