clean_distfiles(const char *directory,
	        const char *prodname,
                const char *platname,
	        dist_t     *dist,
	        const char *subpackage)
{
  char		prodfull[255],
		filename[1024];


  if (subpackage)
    snprintf(prodfull, sizeof(prodfull), "%s-%s", prodname, subpackage);
  else
    strlcpy(prodfull, prodname, sizeof(prodfull));


  if (Verbosity)
    printf("Removing %s temporary files...\n", prodfull);

  snprintf(filename, sizeof(filename), "%s/%s.install", directory, prodfull);
  unlink(filename);

  snprintf(filename, sizeof(filename), "%s/%s.license", directory, prodfull);
  unlink(filename);

  snprintf(filename, sizeof(filename), "%s/%s.patch", directory, prodfull);
  unlink(filename);

  snprintf(filename, sizeof(filename), "%s/%s.psw", directory, prodfull);
  unlink(filename);

  snprintf(filename, sizeof(filename), "%s/%s.psw", directory, prodfull);
  unlink(filename);

  snprintf(filename, sizeof(filename), "%s/%s.readme", directory, prodfull);
  unlink(filename);

  snprintf(filename, sizeof(filename), "%s/%s.remove", directory, prodfull);
  unlink(filename);

  snprintf(filename, sizeof(filename), "%s/%s.ss", directory, prodfull);
  unlink(filename);

  snprintf(filename, sizeof(filename), "%s/%s.sw", directory, prodfull);
  unlink(filename);
}
