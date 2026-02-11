addFormCompletionItem(const QString &name, const QString &value)
{
    if (!m_part->settings()->isFormCompletionEnabled())
        return;


    bool cc_number(true);
    for ( int i = 0; i < value.length(); ++i)
    {
      QChar c(value[i]);
      if (!c.isNumber() && c != '-' && !c.isSpace())
      {
        cc_number = false;
        break;
      }
    }
    if (cc_number)
      return;
    QStringList items = formCompletionItems(name);
    if (!items.contains(value))
        items.prepend(value);
    while ((int)items.count() > m_part->settings()->maxFormCompletionItems())
        items.erase(items.isEmpty() ? items.end() : --items.end());
    d->formCompletions->group("").writeEntry(name, items);
}
