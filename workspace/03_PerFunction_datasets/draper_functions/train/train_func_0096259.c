ldbm_back_ok_to_dump(const char *dn, char **include, char **exclude)
{
    int i = 0;

    if (!(include || exclude))
        return(1);

    if (exclude) {
        i = 0;
        while (exclude[i]) {
            if (slapi_dn_issuffix(dn,exclude[i]))
               return(0);
            i++;
        }
    }

    if (include) {
        i = 0;
        while (include[i]) {
            if (slapi_dn_issuffix(dn,include[i]))
                return(1);
            i++;
        }

        return(0);
    }

    return(1);
}
