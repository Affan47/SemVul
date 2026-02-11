send(int cmd, const QByteArray& arr )
{
   slaveWriteError = false;
   if (!d->appConnection.send(cmd, arr))

       slaveWriteError = true;
   if (slaveWriteError) exit();
}
