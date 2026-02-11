fileutils_fqfname_filename (const char * path)

{
char  *fname;
const char *pc;

int len, j;


ER_TRACE(__func__)


if (path == NULL) return NULL;

len = (int) strlen (path);
j = len;

pc = path + len;

while ((j >= 0) && (*pc != '/'))
   {
   pc--;
   j--;
   }

fname = (char *) cpl_calloc ((size_t) (len - j), (size_t) sizeof (char));
if (fname == NULL) return NULL;

(void) strncpy (fname, &path[j + 1], (size_t) (len-j-1));

return fname;

}
