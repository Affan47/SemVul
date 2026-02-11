aw_help_edit_help(AW_window *aww) {
    char *helpfile = get_full_qualified_help_file_name(aww->get_root(), true);

    if (GB_size_of_file(helpfile)<=0){
#if defined(DEBUG)
        const char *base = GB_path_in_ARBHOME("HELP_SOURCE/oldhelp", NULL);
#else
        const char *base = GB_path_in_ARBLIB("help", NULL);
#endif

        const char *copy_cmd = GBS_global_string("cp %s/FORM.hlp %s", base, helpfile);
        printf("[Executing '%s']\n", copy_cmd);
        system(copy_cmd);
    }

    AWT_edit(helpfile);

    free(helpfile);
}
