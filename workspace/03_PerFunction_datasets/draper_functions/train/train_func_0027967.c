create_mysql_upgrade_info_file(void)
{
  FILE *out;
  char upgrade_info_file[FN_REFLEN]= {0};

  if (get_upgrade_info_file_name(upgrade_info_file))
    return;

  if (!(out= my_fopen(upgrade_info_file, O_TRUNC | O_WRONLY, MYF(0))))
  {
    fprintf(stderr,
            "Could not create the upgrade info file '%s' in "
            "the MySQL Servers datadir, errno: %d\n",
            upgrade_info_file, errno);
    return;
  }


  fputs(MYSQL_SERVER_VERSION, out);
  my_fclose(out, MYF(0));


  if (!upgrade_already_done())
    fprintf(stderr,
            "Could not write to the upgrade info file '%s' in "
            "the MySQL Servers datadir, errno: %d\n",
            upgrade_info_file, errno);
  return;
}
