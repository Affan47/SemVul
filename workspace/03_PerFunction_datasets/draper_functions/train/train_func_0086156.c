sort_dist_files(dist_t *dist)
{
  int		i;
  file_t	*file;


  if (dist->num_files > 1)
    qsort(dist->files, (size_t)dist->num_files, sizeof(file_t),
          (int (*)(const void *, const void *))compare_files);


  for (i = dist->num_files - 1, file = dist->files; i > 0; i --, file ++)
    if (!strcmp(file[0].dst, file[1].dst))
    {
      if (file[0].type == file[1].type && file[0].mode == file[1].mode &&
          !strcmp(file[0].src, file[1].src) &&
          !strcmp(file[0].user, file[1].user) &&
	  !strcmp(file[0].group, file[1].group) &&
	  !strcmp(file[0].options, file[1].options))
      {


	memcpy(file, file + 1, i * sizeof(file_t));
	dist->num_files --;
	file --;
      }
      else
        fprintf(stderr, "epm: Duplicate destination path \"%s\" with different info!\n"
	                "     \"%c %04o %s %s\" from source \"%s\"\n"
			"     \"%c %04o %s %s\" from source \"%s\"\n",
	        file[0].dst,
		file[0].type, file[0].mode, file[0].user, file[0].group, file[0].src,
		file[1].type, file[1].mode, file[1].user, file[1].group, file[1].src);
    }
}
