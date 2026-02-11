getIntValue(const QString& strPath, int iDefault) const
{
   int iRet(0);

   if (m_iConnectionNo >= 0)
   {
      qSettings()->beginReadArray(CONNECTIONS);
      qSettings()->setArrayIndex(m_iConnectionNo);
      iRet = qSettings()->value(strPath, iDefault).toInt(NULL);
      qSettings()->endArray();
   }

   return(iRet);
}
