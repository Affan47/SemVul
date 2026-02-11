title_to_mon(const char *str, int *rank_indx, int *title_length)
{
    int i, j;


    for (i = 0; roles[i].name.m; i++)
    {
        for (j = 0; j < 9; j++)
        {
            if (roles[i].rank[j].m &&
                !strncmpi(str, roles[i].rank[j].m, strlen(roles[i].rank[j].m)))
            {
                if (rank_indx)
                {
                    *rank_indx = j;
                }
                if (title_length)
                {
                    *title_length = strlen(roles[i].rank[j].m);
                }
                return roles[i].malenum;
            }
            if (roles[i].rank[j].f &&
                !strncmpi(str, roles[i].rank[j].f, strlen(roles[i].rank[j].f)))
            {
                if (rank_indx)
                {
                    *rank_indx = j;
                }
                if (title_length)
                {
                    *title_length = strlen(roles[i].rank[j].f);
                }
                return ((roles[i].femalenum != NON_PM) ?
                        roles[i].femalenum : roles[i].malenum);
            }
        }
    }
    return NON_PM;
}
