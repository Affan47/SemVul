find_column(int tab, char *col)
{
    int i;

    for (i = 0; i < db.tables[tab].ncols; i++) {
	if (G_strcasecmp(db.tables[tab].cols[i].name, col) == 0)
	    return (i);
    }
    return (-1);
}
