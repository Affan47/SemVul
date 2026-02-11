build_filelist(char *root_dir, struct z_story_list *story_list,
    bool recursive, struct babel_info *babel)
{
  char *cwd = fsi->get_cwd();
  char *absrootdir;

  if (root_dir == NULL)
  {
    TRACE_LOG("Building filelist for rootdir: \"/\".\n");
    search_dir("/", &new_file_searched, story_list, recursive, babel);
  }
  else
  {
    TRACE_LOG("Building filelist for rootdir: \"%s\".\n", root_dir);

    if ((fsi->ch_dir(root_dir)) == -1)
      detect_and_add_z_file(root_dir, NULL, babel, story_list);
    else
    {

      absrootdir = fsi->get_cwd(NULL, 0);
      search_dir(absrootdir, &new_file_searched, story_list, recursive, babel);
      free(absrootdir);
    }
  }

  fsi->ch_dir(cwd);
  free(cwd);
}
