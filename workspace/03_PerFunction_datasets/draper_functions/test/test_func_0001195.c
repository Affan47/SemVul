readLogLine(char* data, qint64 iMaxSize)
{


   qint64 iRet(m_vpnLogPipe.readLine(data, iMaxSize));

   if (iRet > 0)
   {
      const QString strLine(data);
      const QStringList astrParts(strLine.split(RE_LOG_SPLITLINE));
      ::strcpy(data, astrParts.last().toAscii().data());
      iRet = ::strlen(data);

      if (::strstr(data, STR_LOG_MATCH_CERTIFICATELOADERROR) != NULL)
      {
         m_iReturnCode = ERR_LOADING_CERTIFICATE;
         if (RE_LOG_CAP_CERTIFICATEID.indexIn(data) > 0)
            emitErrorMsg(RE_LOG_CAP_CERTIFICATEID.cap(1));
         else
            emitErrorMsg("unknown");
      }
      if (::strstr(data, STR_LOG_MATCH_AUTHFAILED) != NULL || ::strstr(data, STR_LOG_MATCH_AUTHFAILURE) != NULL)
      {
         m_iReturnCode = ERR_AUTHENTICATION_FAILED;
         emitErrorMsg(connectionName());
      }
      else if (::strstr(data, STR_LOG_MATCH_NO_DATA))
      {
         m_iReturnCode = ERR_WRONG_CERTIFICATE;
         emitErrorMsg(connectionName());
      }
      else if (::strstr(data, STR_LOG_MATCH_PEERAUTHFAILED))
      {
         m_iReturnCode = ERR_NO_SECRET_FOUND;
         emitErrorMsg(connectionName());
      }
      else if (::strstr(data, STR_CONNECT_TIMEOUT))
      {
         m_iReturnCode = ERR_CONNECT_TIMEOUT;
         emitErrorMsg(connectionName());
      }
      else if (!m_fIPSecConnectionAdded)
      {
         m_fIPSecConnectionAdded = strLine.contains(STR_LOG_MATCH_IPSEC_CONNECTIONADDED + "\"" + connectionName() + "\"");
         if (m_fIPSecConnectionAdded) onResult(0, "");
      }
   }


   return(iRet);
}
