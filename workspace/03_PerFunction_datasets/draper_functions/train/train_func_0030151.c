robust_getcwd (struct file_name *file_name)
{
  size_t height = 1;
  struct dev_ino dev_ino_buf;
  struct dev_ino *root_dev_ino = get_root_dev_ino (&dev_ino_buf);
  struct stat dot_sb;

  if (root_dev_ino == NULL)
    error (EXIT_FAILURE, errno, _("failed to get attributes of %s"),
           quote ("/"));

  if (stat (".", &dot_sb) < 0)
    error (EXIT_FAILURE, errno, _("failed to stat %s"), quote ("."));

  while (1)
    {

      if (SAME_INODE (dot_sb, *root_dev_ino))
        break;

      find_dir_entry (&dot_sb, file_name, height++);
    }


  if (file_name->start[0] == '\0')
    file_name_prepend (file_name, "", 0);
}
