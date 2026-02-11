signalDown()
{
  int i, n,
      size,
      sigcomp_nr,
      selected_signals[MAXSIGNALS];

  QList<QListWidgetItem *> selectedlist;

  struct signalcompblock *signalcomp;


  selectedlist = list->selectedItems();

  n = selectedlist.size();

  if(n < 1)
  {
    return;
  }

  size = list->count();

  if(size < (n + 1))
  {
    return;
  }

  if(selectedlist.at(n - 1)->data(Qt::UserRole).toInt() > (size - 2))
  {
    return;
  }

  for(i=(n-1); i>=0; i--)
  {
    sigcomp_nr = selectedlist.at(i)->data(Qt::UserRole).toInt();

    signalcomp = mainwindow->signalcomp[sigcomp_nr];

    mainwindow->signalcomp[sigcomp_nr] = mainwindow->signalcomp[sigcomp_nr + 1];

    mainwindow->signalcomp[sigcomp_nr + 1] = signalcomp;

    selected_signals[i] = sigcomp_nr;
  }

  load_signalcomps();

  for(i=0; i<n; i++)
  {
    list->item(selected_signals[i] + 1)->setSelected(TRUE);
  }

  mainwindow->setup_viewbuf();
}
