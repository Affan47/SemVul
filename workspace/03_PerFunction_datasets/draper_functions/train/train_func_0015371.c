processClientFilters()
{
    std::list<std::string>::const_iterator j;

    for (j = m_inFilters.begin(); j != m_inFilters.end(); j++)
    {
        if (*j == "Gzip") { m_canGzip = true; }
        if (*j == "Bzip2") { m_canBzip2 = true; }
    }
}

}
