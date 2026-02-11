appendLogPlainText(const char* pcText)
{
   const QString strText(pcText);
   const int iPos(strText.indexOf("ipsec__plutorun"));

   m_Widget.m_pTextEdit->insertPlainText(QDateTime::currentDateTime().toString("MMM dd hh:mm:ss.zzz") + " " + strText.mid((iPos == -1 ? 0 : iPos)));
}
