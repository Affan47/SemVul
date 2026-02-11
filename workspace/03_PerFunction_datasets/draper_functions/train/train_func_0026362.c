searcher(void *arg, dir_walk_message_ty msg, string_ty *filename,
    const struct stat *)
{
    static string_ty *the_config_file;

    if (!the_config_file)
        the_config_file = str_from_c("config");
    if (msg == dir_walk_file)
    {
        context_ty      *context;
        format_ty       *fp;

        context = (context_ty *)arg;
        fp = context->fp;
        if (fp->vptr->is_a_candidate(fp, filename))
        {
            string_ty       *relative;
            string_ty       *sanitized;
            format_search_ty *fsp;
            format_version_ty *fvp;

            relative = os_below_dir(context->base, filename);
            sanitized = format_sanitize(fp, relative, 1);
            str_free(relative);
            if (str_equal(sanitized, the_config_file))
                fvp = 0;
            else
                fvp = fp->vptr->read_versions(fp, filename, sanitized);
            fsp = format_search_new();
            fsp->filename_physical = str_copy(filename);
            fsp->filename_logical = sanitized;
            fsp->root = fvp;
            format_search_list_append(context->fslp, fsp);
        }
    }
}
