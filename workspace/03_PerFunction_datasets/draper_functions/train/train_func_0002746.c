scandir_get_entries( const char  * dir,
                     const char  * pat,
                     FL_Dirlist ** dirlist )
{
    static struct DIRENT **dlist;
    FL_Dirlist *dl;
    static int lastn;
    static struct stat ffstat;
    int i,
        n;

    cpat = pat;
    cdir = dir;


    if ( dlist )
    {
        while ( --lastn >= 0 )
            if ( dlist[ lastn ] )
                fl_free( dlist[ lastn ]);
        fl_free( dlist );
        dlist = NULL;
    }

    n = 0;
    if ( ( lastn = tc_scandir( dir, &dlist ) ) > 0 )
    {
        dl = *dirlist = fl_malloc( ( lastn + 1 ) * sizeof **dirlist );
        for ( i = n = 0; i < lastn; i++ )
        {
            if ( fselect( dlist[ i ]->d_name, &ffstat, &dl->type ) )
            {
                dl->name = fl_strdup( dlist[ i ]->d_name );
                dl->dl_mtime = ffstat.st_mtime;
                dl->dl_size = ffstat.st_size;
                dl++;
                n++;
            }
        }

        dl->name = NULL;

        if ( fli_sort_method != FL_NONE )
            qsort( *dirlist, n, sizeof **dirlist, tc_sort );
    }

    return n;
}
