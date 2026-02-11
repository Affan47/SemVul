process_request (client_t *client, char *path)
{
   char *p;
   int rc, pathlen;

   pathlen = strlen(path);
   if (!pathlen)
       return 1;

   if (pathlen >= 12 && memcmp(path, "GET ", 4) == 0)
      {

         char *http_p = path + pathlen - 9;
         if (memcmp(http_p, " HTTP/1.0", 9) && memcmp(http_p, " HTTP/1.1", 9))
            return 1;
         *http_p = 0;
         pathlen = strlen(path + 4);
         memmove(path, path + 4, pathlen + 1);
         client->http = 1;
      }

   if (*path != '/')
       return 1;


   if (strcspn(path, ">!@#$%`;|\"\\'<") < pathlen)
      return 1;

   p = strchr(path, '?');
   if (p)
      {
         *p = 0;
         debug_msg("Found subtree %s and %s", path, p+1);
         rc = processfilter(client, p+1);
         if (rc) return 1;
      }

   return 0;
}
