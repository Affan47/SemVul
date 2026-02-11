ReadDirLocal(CFDIR *dir)
{
int err;
struct dirent *ret;

errno = 0;
err = readdir_r((DIR *)dir->dirh, dir->entrybuf, &ret);

if (err != 0)
   {
   errno = err;
   return NULL;
   }

if (ret == NULL)
   {
   return NULL;
   }

return ret;
}
