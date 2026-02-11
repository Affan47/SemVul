update_who(QString str)
{
  who->clear();
  who->insertStringList(QStringList::split("\n", str));
}
