average_annot(bool)
{
  if(mainwindow->files_open != 1)
  {
    return;
  }

  if(!mainwindow->signalcomps)
  {
    QMessageBox messagewindow(QMessageBox::Critical, "Error", "First add a signal to the screen.");
    messagewindow.exec();

    return;
  }

  if(mainwindow->annot_editor_active)
  {
    QMessageBox messagewindow(QMessageBox::Critical, "Error", "Close the annotation editor and try again.");
    messagewindow.exec();

    return;
  }

  if(list->count() < 1)
  {
    return;
  }

  UI_AveragerWindow average_wndw(mainwindow, list->currentRow());
}
