fail(QString msg)
{
  QMessageBox::warning(0, QLatin1String("Insert image ipelet"),
		       QLatin1String("<qt>") + msg
		       + QLatin1String("</qt>"),
		       QLatin1String("Dismiss"));
}
