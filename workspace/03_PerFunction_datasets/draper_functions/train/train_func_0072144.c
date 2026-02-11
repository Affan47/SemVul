tar_directory(tarf_t     *tar,
              const char *srcpath,
              const char *dstpath)
{
  DIR		*dir;
  DIRENT	*dent;
  char		src[1024],
		dst[1024],
		srclink[1024];
  struct stat	srcinfo;


  if (tar == NULL || srcpath == NULL || dstpath == NULL)
    return (-1);


  if ((dir = opendir(srcpath)) == NULL)
  {
    fprintf(stderr, "epm: Unable to open directory \"%s\": %s\n", srcpath,
            strerror(errno));

    return (-1);
  }


  while ((dent = readdir(dir)) != NULL)
  {


    if (!strcmp(dent->d_name, ".") || !strcmp(dent->d_name, ".."))
      continue;


    snprintf(src, sizeof(src), "%s/%s", srcpath, dent->d_name);
    if (dstpath[0])
      snprintf(dst, sizeof(dst), "%s/%s", dstpath, dent->d_name);
    else
      strlcpy(dst, dent->d_name, sizeof(dst));

    if (stat(src, &srcinfo))
    {
      fprintf(stderr, "epm: Unable to stat \"%s\": %s\n", src,
              strerror(errno));
      continue;
    }


    if (Verbosity)
      puts(dst);

    if (S_ISDIR(srcinfo.st_mode))
    {


      if (tar_header(tar, TAR_DIR, srcinfo.st_mode, 0,
                     srcinfo.st_mtime, "root", "sys", dst, NULL))
        goto fail;

      if (tar_directory(tar, src, dst))
        goto fail;
    }
    else if (S_ISLNK(srcinfo.st_mode))
    {


      if (readlink(src, srclink, sizeof(srclink)) < 0)
        goto fail;

      if (tar_header(tar, TAR_SYMLINK, srcinfo.st_mode, 0,
                     srcinfo.st_mtime, "root", "sys", dst, srclink))
        goto fail;
    }
    else
    {


      if (tar_header(tar, TAR_NORMAL, srcinfo.st_mode, srcinfo.st_size,
                     srcinfo.st_mtime, "root", "sys", dst, NULL))
        goto fail;

      if (tar_file(tar, src))
        goto fail;
    }
  }

  closedir(dir);
  return (0);

  fail:

  closedir(dir);
  return (-1);
}
