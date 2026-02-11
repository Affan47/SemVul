add(const map<string,float>& domainCount,float count,
         const MaybeLog& maybeLog,
         std::vector<float>& denseValues,
         std::map<std::string,float>& sparseValues)  const
{
  typedef map< string, float >::const_iterator I;
  for (I i=domainCount.begin(); i != domainCount.end(); i++) {
      sparseValues["dom_" + i->first] = 1;
  }
}
