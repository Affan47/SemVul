operator()()
{
  size_t lineNum = 0;

  std::vector<std::string> lines;
  size_t max_lines = 1000;
  lines.reserve(max_lines);

  {
#ifdef WITH_THREADS
    boost::mutex::scoped_lock lock(m_fileMutex);
#endif
    std::string line;
    while(lines.size() < max_lines && std::getline(m_inFile, line))
        lines.push_back(line);
    lineNum = m_lineNum;
    m_lineNum += lines.size();
  }

  std::vector<PackedItem> result;
  result.reserve(max_lines);

  while(lines.size())
  {
    for(size_t i = 0; i < lines.size(); i++)
    {
      std::vector<std::string> tokens;
      Moses::TokenizeMultiCharSeparator(tokens, lines[i], m_creator.m_separator);

      std::string encodedLine = m_creator.EncodeLine(tokens);

      std::string f = tokens[0];

      std::string e;
      if(tokens.size() > 2)
        e = tokens[1];

      PackedItem packedItem(lineNum + i, m_creator.MakeSourceTargetKey(f, e),
                            encodedLine, i);
      result.push_back(packedItem);
    }
    lines.clear();

    {
#ifdef WITH_THREADS
      boost::mutex::scoped_lock lock(m_mutex);
#endif
      for(size_t i = 0; i < result.size(); i++)
        m_creator.AddEncodedLine(result[i]);
      m_creator.FlushEncodedQueue();
    }

    result.clear();
    lines.reserve(max_lines);
    result.reserve(max_lines);

#ifdef WITH_THREADS
    boost::mutex::scoped_lock lock(m_fileMutex);
#endif
    std::string line;
    while(lines.size() < max_lines && std::getline(m_inFile, line))
      lines.push_back(line);
    lineNum = m_lineNum;
    m_lineNum += lines.size();
  }
}
