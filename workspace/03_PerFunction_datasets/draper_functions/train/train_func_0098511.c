error(const char *s1, const char *s2, const char *s3)
{
  cerr << "Error: ";
  cerr << s1;
  if(s2 != NULL && strlen(s2) > 0)
    cerr << " " << s2;
  if(s3 != NULL && strlen(s3) > 0)
    cerr << " " << s3;
  cerr << endl;
}
