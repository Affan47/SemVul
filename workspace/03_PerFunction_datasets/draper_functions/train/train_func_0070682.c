saveXml(QTextStream& xmlStream) const
{

  xmlStream << "<goal player=\"";
  if (m_player != 0)
  {
    xmlStream << m_player->name();
  }
  xmlStream << "\" type=\"" << m_type << "\" description=\"" << m_description;
  xmlStream << "\" nbCountries=\"" << m_nbCountries << "\" nbArmiesByCountry=\"" << m_nbArmiesByCountry << "\">" << endl;
  xmlStream << "<continents>" << endl;
  QList<QString>::ConstIterator itc, itc_end;
  itc = continents().constBegin(); itc_end = continents().constEnd();
  for (; itc != itc_end; itc++)
  {
    QString name = (*itc==QString())?"":(*itc);
    xmlStream << "<continent name=\"" << name << "\"/>" << endl;
  }
  xmlStream << "</continents>" << endl;
  xmlStream << "<players>" << endl;
  QList<QString>::ConstIterator itp, itp_end;
  itp = m_players.constBegin(); itp_end = m_players.constEnd();
  for (; itp != itp_end; itp++)
  {
    xmlStream << "<player name=\"" << (*itp) << "\"/>" << endl;
  }
  xmlStream << "</players>" << endl;
  xmlStream << "</goal>" << endl;
}

}

}
