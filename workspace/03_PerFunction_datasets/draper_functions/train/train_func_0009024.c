getNgramLikeTable(const Ngram ngram, int limit) const
{
    std::stringstream query;
    query << "SELECT " << buildSelectLikeClause(ngram.size()) << " "
          << "FROM _" << ngram.size() << "_gram"
          << buildWhereLikeClause(ngram)
          << " ORDER BY count DESC";
    if (limit < 0) {
        query << ";";
    } else {
        query << " LIMIT " << limit << ';';
    }

    return executeSql(query.str());
}
