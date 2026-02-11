runDontChangeHostname(const QByteArray &oldName, const QByteArray &newName)
{
   QStringList args;
   args.append(QFile::decodeName(oldName));
   args.append(QFile::decodeName(newName));
   KToolInvocation::kdeinitExecWait( "kdontchangethehostname", args );
}
