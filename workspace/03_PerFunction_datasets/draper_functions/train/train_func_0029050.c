slotHigh(const QString &text)
{
  int limit = text.toInt();


  if (limit > colorAttributeMax())
  {
    limit = colorAttributeMax();

    if (m_showLarge)
    {
      ASSERT_ENGAUGE(editHigh != 0);
      editHigh->setText(QString("%1").arg(limit));
    }
  }

  ASSERT_ENGAUGE(dividerUpper);
  dividerUpper->setLimit(limit);


  if (text.isEmpty())
    passLimitToParent(false, colorAttributeMax() + 1);
  else
    passLimitToParent(false, limit);
}
