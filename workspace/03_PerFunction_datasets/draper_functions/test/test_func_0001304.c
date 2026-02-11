setRouteProperty(const QString& strValue, int iRow, const QString& strPropertyName) const
{
   bool fRet(m_iConnectionNo >= 0 && qSettings()->isWritable());

   if (fRet)
   {
      qSettings()->beginReadArray(CONNECTIONS);
      qSettings()->setArrayIndex(m_iConnectionNo);
      qSettings()->beginGroup(IP);

      const int iSize(qSettings()->beginReadArray(ROUTES));
      if (iRow < iSize)
      {
         qSettings()->setArrayIndex(iRow);
         if  (qSettings()->value(strPropertyName) != strValue)
            qSettings()->setValue(strPropertyName, strValue);
      }
      else
         fRet = false;

      qSettings()->endArray();

      qSettings()->endGroup();
      qSettings()->endArray();
   }

   return(fRet);
}
