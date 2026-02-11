rename_in_schema_file(THD *thd,
                              const char *schema, const char *old_name,
                              const char *new_db, const char *new_name)
{
  char old_path[FN_REFLEN + 1], new_path[FN_REFLEN + 1], arc_path[FN_REFLEN + 1];

  build_table_filename(old_path, sizeof(old_path) - 1,
                       schema, old_name, reg_ext, 0);
  build_table_filename(new_path, sizeof(new_path) - 1,
                       new_db, new_name, reg_ext, 0);

  if (mysql_file_rename(key_file_frm, old_path, new_path, MYF(MY_WME)))
    return 1;


  build_table_filename(arc_path, sizeof(arc_path) - 1, schema, "arc", "", 0);

  {
    MY_DIR *new_dirp;
    if ((new_dirp = my_dir(arc_path, MYF(MY_DONT_SORT))))
    {
      DBUG_PRINT("my",("Archive subdir found: %s", arc_path));
      (void) mysql_rm_arc_files(thd, new_dirp, arc_path);
    }
  }
  return 0;
}
