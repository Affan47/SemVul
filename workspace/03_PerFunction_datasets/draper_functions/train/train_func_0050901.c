set_fileconverter(const char *fc)
{
    int i;
    for (i = 0; fileconverters[i][0]; i++) {
      if (!strcmp(fc, fileconverters[i][0])) {
            strlcpy(fileconverter, fileconverters[i][1], PATH_MAX);
	    break;
      }
    }
    if (!fileconverters[i][0])
        strlcpy(fileconverter, fc, PATH_MAX);
}
