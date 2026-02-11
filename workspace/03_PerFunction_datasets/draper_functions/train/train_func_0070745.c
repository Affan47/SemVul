showStatusMessage(const QString & message, int timeout)
{
  if (! d->statusBar)
    d->statusBar = QMainWindow::statusBar();
  if (! timeout)
    d->statusMessage = message;
  if (d->statusBar)
    d->statusBar->showMessage(message, timeout);
}
