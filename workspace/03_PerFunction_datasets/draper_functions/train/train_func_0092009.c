GenerateDeletedCharacterGUIDsWhereStr(DeletedInfoList::const_iterator& itr, DeletedInfoList::const_iterator const& itr_end)
{
    std::ostringstream wherestr;
    wherestr << "guid IN ('";
    for (; itr != itr_end; ++itr)
    {
        wherestr << itr->lowguid;

        if (wherestr.str().size() > MAX_QUERY_LEN - 50)
        {
            ++itr;
            break;
        }

        DeletedInfoList::const_iterator itr2 = itr;
        if (++itr2 != itr_end)
            { wherestr << "','"; }
    }
    wherestr << "')";
    return wherestr.str();
}
