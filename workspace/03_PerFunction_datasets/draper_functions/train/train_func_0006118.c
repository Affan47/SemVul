open_include(
    char *  filename,
    int     searchlocal,
    int     next
)


{
    char    src_dir[ PATHMAX] = { EOS, };
    int     full_path;
    int     has_dir = FALSE;
    int     has_dir_src = FALSE;
    int     has_dir_fname = FALSE;

    full_path = is_full_path( filename);

    if (!full_path && searchlocal && (search_rule & SOURCE)) {
        has_dir_src  = has_directory( infile->src_dir, src_dir);
        has_dir_fname = has_directory( infile->real_fname
                , src_dir + strlen( src_dir));


        has_dir = has_dir_src || has_dir_fname
                || (**(infile->dirp) != EOS);
    }
    if (mcpp_debug & PATH)
        mcpp_fprintf( DBG, "filename: %s\n", filename);

#if COMPILER == GNUC
    if (! full_path) {
        if (i_split
                || next)
        goto  search_dirs;
    }
#endif

    if ((searchlocal && ((search_rule & CURRENT) || !has_dir)) || full_path) {


        if (open_file( &null, NULL, filename, searchlocal && !full_path
                , FALSE, FALSE))
            return  TRUE;
        if (full_path)
            return  FALSE;
    }

    if (searchlocal && (search_rule & SOURCE) && has_dir) {


        if (open_file( infile->dirp, src_dir, filename, TRUE, FALSE, FALSE))
            return  TRUE;
    }

#if COMPILER == MSC
    if (searchlocal) {

        FILEINFO *  file = infile;
        while ((file = file->parent) != NULL) {

            if (open_file( file->dirp, src_dir, filename, TRUE, FALSE, FALSE))
                return  TRUE;
        }
    }
#endif
#if COMPILER == GNUC
search_dirs:
    if (searchlocal) {

        const char **   qdir;
        for (qdir = quote_dir; qdir < quote_dir_end; qdir++) {
            if (open_file( qdir, NULL, filename, FALSE, FALSE, FALSE))
                return  TRUE;
        }
    }
#endif

    if (search_dir( filename, searchlocal, next))
        return  TRUE;

    return  FALSE;
}
