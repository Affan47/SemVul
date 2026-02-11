OpenDirLocal(const char *dirname)
{
CFDIR *ret;
if ((ret = calloc(1, sizeof(CFDIR))) == NULL)
   {
   FatalError("Unable to allocate memory for CFDIR");
   }
DIR *dirh;

ret->dirh = dirh  = opendir(dirname);
if (dirh == NULL)
   {
   free(ret);
   return NULL;
   }

size_t dirent_buf_size = GetDirentBufferSize(GetNameMax(dirh));
if (dirent_buf_size == (size_t)-1)
   {
   FatalError("Unable to determine directory entry buffer size for directory %s", dirname);
   }

if ((ret->entrybuf = calloc(1, dirent_buf_size)) == NULL)
   {
   FatalError("Unable to allocate memory for directory entry buffer for directory %s", dirname);
   }

return ret;
}
