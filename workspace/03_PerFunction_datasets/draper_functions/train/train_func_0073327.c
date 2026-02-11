add(const domain_list& arg)
  {

    for (dolci p=arg.m_list.begin(); p != arg.m_list.end(); ++p)
      m_list.push_back(*p);

    return *this;
  }
}
