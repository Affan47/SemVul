prune(const data_mask& dm, const unsigned int col)
  {
    std::vector<std::vector<double>::iterator> iter(m_data.size());
    for (unsigned int i = 0; i < m_data.size(); i++)
      iter.at(i) = m_data.at(i).begin();

    while (iter.at(0) != m_data.at(0).end())
      {
	if ( dm.masks(*iter.at(col-1)) )
	  for (unsigned int j = 0; j < m_data.size(); j++)
	    m_data.at(j).erase(iter.at(j));

	else
	  for (unsigned int j = 0; j < m_data.size(); j++)
	    iter.at(j)++;
      }

    return *this;
  }
