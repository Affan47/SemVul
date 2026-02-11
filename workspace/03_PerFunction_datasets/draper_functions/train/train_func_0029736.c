show(QWidget * )
{
  adjust();
  if (mContainerBase) { mContainerBase->show(); }
  QDialog::show();
}
