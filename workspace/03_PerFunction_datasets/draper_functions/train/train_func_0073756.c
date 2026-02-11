packrat_find_object(const char * object, unsigned short cmpop, const char * version)
{
  Log(object);


  char real_path[1024];
  struct packrat_object * ob = 0;

  if (packrat_find_file(object, real_path,sizeof(real_path))) {
	Log("Found file");
	if (cmpop == PACKRAT_CMP_NONE) {
	  ob = malloc(sizeof(struct packrat_object *));
	  return ob;
	}
	Log("Version check not yet implemented");
  } else if (packrat_find_package(object)) {
  } else {
	return 0;
  }


  return 0;
}
