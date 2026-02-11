send(ResponseType responseType, ResponseInformation responseInformation)
{
   bool fRet = false;

   if (m_pSocket->state() == QLocalSocket::ConnectedState)
   {
      m_pSocket->write((QString::number(responseType) + " " + QString::number(responseInformation) + '\n').toAscii().constData());
      fRet = true;
   }

   return(fRet);
}
