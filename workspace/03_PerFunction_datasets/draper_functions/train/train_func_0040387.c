cat_str(char *s1,
	     char *s2,
	     char *s3)
{
  int i, j;

  for (i = 0; s1[i] != '\0'; i++)
    s3[i] = s1[i];
  for (j = 0; s2[j] != '\0'; j++, i++)
    s3[i] = s2[j];
  s3[i] = '\0';
}
