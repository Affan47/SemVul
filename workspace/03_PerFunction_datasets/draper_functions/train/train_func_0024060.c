uninit_options(struct program_options *options)
{
    options->round_size = DFLT_OPT_ROUND_SIZE;
    options->overload_size = DFLT_OPT_OVERLOAD_SIZE;
    options->preload_size = DFLT_OPT_PRELOAD_SIZE;
    if(options->post_part_hook != NULL)
        free(options->post_part_hook);
    if(options->pre_part_hook != NULL)
        free(options->pre_part_hook);
    options->live_mode = DFLT_OPT_LIVEMODE;
    options->leaf_dirs = DFLT_OPT_LEAFDIRS;
    options->dir_depth = DFLT_OPT_DIR_DEPTH;
    options->dnr_empty = DFLT_OPT_DNREMPTY;
    options->empty_dirs = DFLT_OPT_EMPTYDIRS;
    if(options->exclude_files_ci != NULL)
        str_cleanup(&(options->exclude_files_ci),
            &(options->nexclude_files_ci));
    if(options->exclude_files != NULL)
        str_cleanup(&(options->exclude_files),
            &(options->nexclude_files));
    if(options->include_files_ci != NULL)
        str_cleanup(&(options->include_files_ci),
            &(options->ninclude_files_ci));
    if(options->include_files != NULL)
        str_cleanup(&(options->include_files),
            &(options->ninclude_files));
    options->cross_fs_boundaries = DFLT_OPT_CROSSFSBOUNDARIES;
    options->follow_symbolic_links = DFLT_OPT_FOLLOWSYMLINKS;
    options->verbose = DFLT_OPT_VERBOSE;
    options->add_slash = DFLT_OPT_ADDSLASH;
    if(options->out_filename != NULL)
        free(options->out_filename);
    options->arbitrary_values = DFLT_OPT_ARBITRARYVALUES;
    if(options->in_filename != NULL)
        free(options->in_filename);
    options->max_size = DFLT_OPT_MAX_SIZE;
    options->max_entries = DFLT_OPT_MAX_ENTRIES;
    options->num_parts = DFLT_OPT_NUM_PARTS;
}
