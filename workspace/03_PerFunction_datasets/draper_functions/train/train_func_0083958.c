variableLine()
{
  for (int i = 0; i < m_items.size(); ++i) {
    VariableItem* item = m_items[i];

    if (item->isActive()) {
      m_variables[item->variable()] = item->valueAsString();
    } else if (m_variables.contains(item->variable())) {
      m_variables.remove(item->variable());
    }
  }

  QString line;
  QMap<QString, QString>::const_iterator it = m_variables.constBegin();
  while (it != m_variables.constEnd()) {
    if (!line.isEmpty()) {
      line += " ";
    }
    line += it.key() + ' ' + it.value() + ';';

    ++it;
  }

  line.prepend("kate: ");

  return line;
}
