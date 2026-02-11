remoteEncoding()
{
   if (d->remotefile)
      return d->remotefile;

   const QByteArray charset (metaData(QLatin1String("Charset")).toLatin1());
   return (d->remotefile = new KRemoteEncoding( charset ));
}
