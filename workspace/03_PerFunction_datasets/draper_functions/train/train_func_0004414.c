slotUpButton()
{
  ToolBarItem *item = m_activeList->currentItem();

  if (!item) {
    Q_ASSERT(false);
    return;
  }

  int row = item->listWidget()->row(item) - 1;

  if (row < 0) {
    Q_ASSERT(false);
    return;
  }


  emit m_widget->enableOk(true);

  moveActive( item, static_cast<ToolBarItem*>(item->listWidget()->item(row - 1)) );
}
