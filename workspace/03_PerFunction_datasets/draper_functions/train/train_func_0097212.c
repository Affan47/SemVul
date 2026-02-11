IsHomeDir(char *name)


{ char *sp;
  struct Item *ip;
  int slashes;

if (name == NULL || strlen(name) == 0)
   {
   return false;
   }

if (VMOUNTLIST == NULL)
   {
   return (false);
   }

for (ip = VHOMEPATLIST; ip != NULL; ip=ip->next)
   {
   slashes = 0;

   for (sp = ip->name; *sp != '\0'; sp++)
      {
      if (*sp == '/')
         {
         slashes++;
         }
      }

   for (sp = name+strlen(name); (*(sp-1) != '/') && (sp >= name) && (slashes >= 0); sp--)
      {
      if (*sp == '/')
         {
         slashes--;
         }
      }


   if (WildMatch(ip->name,sp))
      {
      Debug("IsHomeDir(true)\n");
      return(true);
      }
   }

Debug("IsHomeDir(%s,false)\n",name);
return(false);
}
