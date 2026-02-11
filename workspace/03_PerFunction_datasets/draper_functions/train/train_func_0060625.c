AddFactor(const StringPiece &factorString)
{

#ifdef WITH_THREADS

#if BOOST_VERSION < 104200
  FactorFriend to_ins;
  to_ins.in.m_string.assign(factorString.data(), factorString.size());
#endif
  {
    boost::shared_lock<boost::shared_mutex> read_lock(m_accessLock);
#if BOOST_VERSION >= 104200

    Set::const_iterator i = m_set.find(factorString, HashFactor(), EqualsFactor());
#else
    Set::const_iterator i = m_set.find(to_ins);
#endif
    if (i != m_set.end()) return &i->in;
  }
  boost::unique_lock<boost::shared_mutex> lock(m_accessLock);
#if BOOST_VERSION >= 104200
  FactorFriend to_ins;
  to_ins.in.m_string.assign(factorString.data(), factorString.size());
#endif

#else

#if BOOST_VERSION >= 104200
  Set::const_iterator i = m_set.find(factorString, HashFactor(), EqualsFactor());
  if (i != m_set.end()) return &i->in;
#endif
  FactorFriend to_ins;
  to_ins.in.m_string.assign(factorString.data(), factorString.size());

#endif
  to_ins.in.m_id = m_factorId;
  std::pair<Set::iterator, bool> ret(m_set.insert(to_ins));
  if (ret.second) {
    m_factorId++;
  }
  return &ret.first->in;
}
