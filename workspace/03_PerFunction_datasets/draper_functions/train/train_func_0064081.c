subElementRect(SubElement element, const QStyleOption *option, const QWidget *widget) const
{
  if (element == SE_LineEditContents) {
      KLineEditStyle *unconstThis = const_cast<KLineEditStyle *>(this);

    if (m_sentinel) {

        unconstThis->m_subStyle.clear();
    }

    unconstThis->m_sentinel = true;
    QStyle *s = m_subStyle ? m_subStyle.data() : style();
    QRect rect = s->subElementRect(SE_LineEditContents, option, widget);
    unconstThis->m_sentinel = false;

    if (option->direction == Qt::LeftToRight) {
        return rect.adjusted(0, 0, -m_overlap, 0);
    } else {
        return rect.adjusted(m_overlap, 0, 0, 0);
    }
  }

  return KdeUiProxyStyle::subElementRect(element, option, widget);
}
