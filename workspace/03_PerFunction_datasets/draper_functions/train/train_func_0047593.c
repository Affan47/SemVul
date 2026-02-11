findProtocol(const QString &protocol)
{
  if (!sycocaDict()) return KProtocolInfo::Ptr();

  QMap<QString,KProtocolInfo::Ptr>::iterator it = m_cache.find(protocol);
  if (it != m_cache.end())
     return *it;

  int offset;

  offset = sycocaDict()->find_string( protocol );

  if (!offset) return KProtocolInfo::Ptr();

  KProtocolInfo::Ptr info(createEntry(offset));

  if (info && (info->name() != protocol))
  {

     return KProtocolInfo::Ptr();
  }
  m_cache.insert(protocol,info);
  return info;
}
