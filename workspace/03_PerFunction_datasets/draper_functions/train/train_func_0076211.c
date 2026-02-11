SetQuery(size_t index, const char *sql)
{
    if(m_queries.size() <= index)
    {
        sLog.outError("Query index (" SIZEFMTD ") out of range (size: " SIZEFMTD ") for query: %s", index, m_queries.size(), sql);
        return false;
    }

    if(m_queries[index].first != NULL)
    {
        sLog.outError("Attempt assign query to holder index (" SIZEFMTD ") where other query stored (Old: [%s] New: [%s])",
            index,m_queries[index].first,sql);
        return false;
    }


    m_queries[index] = SqlResultPair(mangos_strdup(sql), (QueryResult*)NULL);
    return true;
}
