_k_slotCurrentPageChanged(const QModelIndex &current, const QModelIndex &before)
{
  KPageWidgetItem *currentItem = 0;
  if ( current.isValid() )
    currentItem = model()->item( current );

  KPageWidgetItem *beforeItem = 0;
  if ( before.isValid() )
    beforeItem = model()->item( before );

    Q_Q(KPageWidget);
    emit q->currentPageChanged(currentItem, beforeItem);
}
