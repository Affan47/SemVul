slotTextChanged(const QString &)
{
   element()->m_value = KUrl( widget()->url() ).pathOrUrl();
}
