locateResource(const char *uri, const char *file) {
    tString filepath, a_uri = tString(), savepath;
    int rv;

    char * to_free = NULL;

    {
        char const *pos, *posb;
        char *nf;
        size_t l;


        if ( (pos = strchr(file, '(')) ) {
            l = (size_t)(pos - file);
            nf = (char*)malloc((l + 1) * sizeof(char));
            strncpy(nf, file, l);
            nf[l] = '\0';
            file = nf;
            to_free = nf;


            ++pos;
            if ( (posb = strchr(pos, ')')) ) {
                l = (size_t)(posb - pos);
                nf = (char*)malloc((l + 1) * sizeof(char));
                strncpy(nf, pos, l);
                nf[l] = '\0';
                a_uri << nf << ';';
                free( nf );
            }
        }
    }

    if (!file || file[0] == '\0') {
        con << tOutput( "$resource_no_filename" );
        return (tString) NULL;
    }
    if (file[0] == '/' || file[0] == '\\') {
        con << tOutput( "$resource_abs_path" );
        return (tString) NULL;
    }
    savepath = tDirectories::Resource().GetWritePath(file);
    if (savepath == "") {
        con << tOutput( "$resource_no_writepath" );
        return (tString) NULL;
    }


    filepath = tDirectories::Resource().GetReadPath(file);

    if (filepath != "")
    {
        if ( NULL != to_free )
            free( to_free );
        return filepath;
    }


    if (uri && strcmp("0", uri))
        a_uri << uri << ';';


    if ( resRepoServer.Len() > 2 )
        a_uri << resRepoServer << file << ';';

    if ( resRepoClient.Len() > 2 && resRepoClient != resRepoServer )
        a_uri << resRepoClient << file << ';';

    con << tOutput( "$resource_not_cached", file );

    rv = myFetch((const char *)a_uri, file, (const char *)savepath);

    if ( NULL != to_free )
        free( to_free );

    if (rv)
        return (tString) NULL;
    return savepath;
}
