sge_unlink(const char *prefix, const char *suffix)
{
   int status;
   stringT str;

   DENTER(TOP_LAYER, "sge_unlink");

   if (!suffix) {
      ERROR((SGE_EVENT, MSG_POINTER_SUFFIXISNULLINSGEUNLINK ));
      DEXIT;
      return false;
   }

   if (prefix) {
      sprintf(str, "%s/%s", prefix, suffix);
   } else {
      sprintf(str, "%s", suffix);
   }

   DPRINTF(("file to unlink: \"%s\"\n", str));
   status = unlink(str);

   if (status) {
      ERROR((SGE_EVENT, "ERROR: unlinking "SFQ": "SFN"\n", str, strerror(errno)));
      DEXIT;
      return false;
   } else {
      DEXIT;
      return true;
   }
}
