execute()
{
    if (!isPrepared())
        return false;

    if (mysql_stmt_execute(m_stmt))
    {
        sLog.outError("SQL: cannot execute '%s'", m_szFmt.c_str());
        sLog.outError("SQL ERROR: %s", mysql_stmt_error(m_stmt));
        return false;
    }

    return true;
}
