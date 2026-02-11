onVpnTaskErrorMsg(int iErrorCode)
{


   char acBuf[1024];

   const qint64 iLineLength = m_pVPNControlTask->readErrorLine(acBuf, sizeof(acBuf));
   if (iLineLength > 0)
   {
      m_pConnectionInformation->appendLogColorText(QColor(255, 0, 0), acBuf);
      error(iErrorCode);
   }


}
