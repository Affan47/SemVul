gotInput()
{
   int cmd;
   QByteArray data;
   if (mConn.read( &cmd, data) == -1)
   {


      deleteLater();
   }
   else if (cmd == MSG_SLAVE_ACK)
   {
      deleteLater();
   }
   else if (cmd != MSG_SLAVE_STATUS)
   {
      kError(7016) << "SlavePool: Unexpected data from slave." << endl;
      deleteLater();
   }
   else
   {
      QDataStream stream( data );
      PIDType<sizeof(pid_t)>::PID_t stream_pid;
      pid_t pid;
      QByteArray protocol;
      QString host;
      qint8 b;
      stream >> stream_pid >> protocol >> host >> b;
      pid = stream_pid;

      if (!stream.atEnd())
      {
         KUrl url;
         stream >> url;
         mOnHold = true;
         mUrl = url;
      }

      mPid = pid;
      mConnected = (b != 0);
      mProtocol = QString::fromLatin1(protocol);
      mHost = host;
      emit statusUpdate(this);
   }
}
