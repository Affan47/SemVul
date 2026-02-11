stateName() const
{
  if (m_state >= (int) sizeof(GameStateNames))
  {
    QString string;
    QTextStream oss(&string);
    oss << "Invalid stored state id: " << m_state;
    kError() << string << endl;
    return string;
  }
  else
  {
    return QString::fromUtf8(GameStateNames[m_state]);
  }
}
