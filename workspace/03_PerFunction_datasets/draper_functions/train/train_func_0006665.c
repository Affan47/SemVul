innerSaveXml(QTextStream& xmlStream)
{
  QString theName = name();
  theName = theName.replace("&","&amp;");
  theName = theName.replace("<","&lt;");
  theName = theName.replace(">","&gt;");
  xmlStream << " name=\"" << theName << "\"";
  xmlStream << " nbCountries=\"" << m_nbCountries << "\"";
  xmlStream << " nbAvailArmies=\"" << m_distributionData.nbToPlace() << "\"";
  xmlStream << " nbAttack=\"" << m_nbAttack << "\"";
  xmlStream << " nbDefense=\"" << m_nbDefense << "\"";
  QString nationName = m_nation->name();
  nationName = nationName.replace("&","&amp;");
  nationName = nationName.replace("<","&lt;");
  nationName = nationName.replace(">","&gt;");
  xmlStream << " nation=\"" << nationName << "\"";
  xmlStream << " password=\"" << KStringHandler::obscure(m_password.value()) << "\"";
  xmlStream << " local=\"" << (isVirtual()?"false":"true") << "\"";
}
