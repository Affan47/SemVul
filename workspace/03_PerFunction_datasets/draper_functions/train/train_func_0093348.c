PrependPackageItem(struct CfPackageItem **list,char *name,char *version,char *arch,struct Attributes a,struct Promise *pp)

{ struct CfPackageItem *pi;

if (strlen(name) == 0 || strlen(version) == 0 || strlen(arch) == 0)
   {
   return false;
   }

CfOut(cf_verbose,""," -> Package (%s,%s,%s) found",name,version,arch);

if ((pi = (struct CfPackageItem *)malloc(sizeof(struct CfPackageItem))) == NULL)
   {
   CfOut(cf_error,"malloc","Can't allocate new package\n");
   return false;
   }

if (list)
   {
   pi->next = *list;
   }
else
   {
   pi->next = NULL;
   }

pi->name = strdup(name);
pi->version = strdup(version);
pi->arch = strdup(arch);
*list = pi;


pi->pp = DeRefCopyPromise("this",pp);
return true;
}
