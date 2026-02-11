addAllColumnsToQuery(Query *q)
{
    for (_columns_t::iterator it = _columns.begin();
            it != _columns.end();
            ++it)
    {
        q->addColumn(it->second);
    }
}
