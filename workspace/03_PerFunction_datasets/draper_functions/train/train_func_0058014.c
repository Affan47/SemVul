extractStatusBar(QMainWindow *mw)
{

  QLayout *layout = mw->layout();
  QLayoutItem *item = 0;
  QStatusBar *sb = 0;
  if (layout)
    for (int i=0; (item = layout->itemAt(i)); i++)
      if ((sb = qobject_cast<QStatusBar*>(item->widget())))
        {
          item = layout->takeAt(i);
          sb->hide();
          sb->setParent(0);
          delete item;
          return sb;
        }
  return 0;
}
