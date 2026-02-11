fileutils_copy (const char * srcpath, const char * dstpath)

{
char *buf;

int src, dst;
int rbytes = 0;
int wbytes = 0;
int blksize = DEV_BLOCKSIZE;

struct stat sb, db;


ER_TRACE(__func__)

if ((stat(srcpath,&sb) == 0) && (stat(dstpath,&db) == 0))
   {
   if (ER_TRACEFLAG)
      {
      (void) sprintf(trace_msg, "in-inode = %d, out-inode = %d",
                     sb.st_ino,db.st_ino);
      ER_TRACEX(trace_msg)
      }
   if (sb.st_ino == db.st_ino)
      return 99;
   }

if ((src = open (srcpath, O_RDONLY)) == -1) return (-1);

if ((fstat (src, &sb) == -1) || (!S_ISREG (sb.st_mode)))
   {
   (void) close (src);
   return -2;
   }

if ((dst = open (dstpath, O_CREAT | O_WRONLY | O_TRUNC, sb.st_mode)) == -1)
   {
   (void) close (src);
   return -3;
   }

if ((fstat (dst, &db) == -1) || (!S_ISREG (db.st_mode)))
   {
   (void) close (src);
   (void) close (dst);
   (void) unlink (dstpath);
   return -4;
   }

#ifdef HAVE_ST_BLKSIZE
blksize = db.st_blksize;
#else
#   ifdef DEV_BSIZE
blksize = DEV_BSIZE;
#   endif
#endif

if ((buf = (char *) cpl_malloc ((size_t)blksize)) == NULL)
   {
   (void) close (src);
   (void) close (dst);
   (void) unlink (dstpath);
   return -5;
   }

while ((rbytes = (int) read (src, buf, (size_t)blksize)) > 0)
   {
   if ((wbytes = (int) write (dst, buf, (size_t)rbytes)) != rbytes)
      {
      wbytes = -1;
      break;
      }
   }

(void) close (src);
(void) close (dst);
cpl_free (buf);


if ((rbytes == -1) || (wbytes == -1))
   {
   (void) unlink (dstpath);
   return -6;
   }

return 0;

}
