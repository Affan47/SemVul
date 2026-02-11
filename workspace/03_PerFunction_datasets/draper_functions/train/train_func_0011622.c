RunQueryValue(const DBProvider * pdb, const char *query)
{
    RowSet *rs;
    rs = pdb->Select(query);
    if (rs && rs->rows > 1) {
        int id = (int)strtol(rs->data[1][0], NULL, 0);
        FreeRowset(rs);
        return id;
    } else
        return -1;
}
