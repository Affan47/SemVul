ListTreeFindPath(Widget w, ListTreeItem * item,
                               char *name, char *path, char delim)
#else
ListTreeItem* ListTreeFindPath(w, item, name, path, delim)
Widget w;
ListTreeItem * item;
char *name;
char *path;
char delim
#endif
{
   ListTreeItem *ret = NULL, *child;
   char *buf=NULL, *bufp;

   TreeCheck(lw, "in ListTreeFindPath");

   if (name == NULL)
      delim = '.';

   if (name == NULL || !strcmp(name, "*") || !strncmp(name, item->text, strlen(name))) {
      if (*path == 0) {
         if (name)
            ret = item;
         return ret;
      }


      bufp = buf = (char *)malloc(strlen(path)+1);
      if (*path == '.' || *path == '/')
         delim = *path++;
      while (*path && *path != '.' && *path != '/')
         *bufp++ = *path++;
      *bufp = 0;
      name = buf;
   } else if (delim == '/')
      return NULL;

   for (child=item->firstchild; child && !ret; child=child->nextsibling)
      ret = ListTreeFindPath(w, child, name, path, delim);

   if (buf) free(buf);
   return ret;
}
