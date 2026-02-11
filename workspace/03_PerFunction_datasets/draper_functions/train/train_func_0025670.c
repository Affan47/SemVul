checkdir()
{
  if(access(atfsit ? "AtFS" : "RCS", 0) != 0){
    if(!qflag || debugon)
      printf("Cannot find \"%s\" directory.  Creating...\n", atfsit ? "AtFS" : "RCS");
    if(strcmp(rcsdir, atfsit ? "AtFS" : "RCS") != 0) {
      if(symlink(rcsdir, atfsit ? "AtFS" : "RCS") != 0)
	fatal2("Symbolic link of %s to %s failed.", rcsdir, atfsit ? "AtFS" : "RCS");
    } else {
      if(mkdir(rcsdir, 0755) != 0)
	fatal1("Cannot create \"%s\" directory.", rcsdir);
    }
  }
}
