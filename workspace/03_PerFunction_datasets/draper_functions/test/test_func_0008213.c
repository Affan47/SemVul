setup()
{
  QPrintDialog dialog(this);
  dialog.setFromTo(fromPage(), toPage());

  dialog.addEnabledOption(QPrintDialog::PrintToFile);
  dialog.addEnabledOption(QPrintDialog::PrintPageRange);
  dialog.addEnabledOption(QPrintDialog::PrintCollateCopies);

  return (dialog.exec() == QDialog::Accepted);
}
