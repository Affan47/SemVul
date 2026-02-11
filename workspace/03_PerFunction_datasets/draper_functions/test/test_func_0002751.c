KeepServerRolePromise(struct Promise *pp)

{ struct Constraint *cp;
  struct Rlist *rp;
  struct Auth *ap;

if (!GetAuthPath(pp->promiser,ROLES))
   {
   InstallServerAuthPath(pp->promiser,&ROLES,&ROLESTOP);
   }

ap = GetAuthPath(pp->promiser,ROLES);

for (cp = pp->conlist; cp != NULL; cp = cp->next)
   {
   if (!IsDefinedClass(cp->classes))
      {
      continue;
      }

   switch (cp->type)
      {
      case CF_LIST:

          for (rp = (struct Rlist *)cp->rval; rp != NULL; rp=rp->next)
             {
             if (strcmp(cp->lval,CF_REMROLE_BODIES[cfs_authorize].lval) == 0)
                {
                PrependItem(&(ap->accesslist),rp->item,NULL);
                continue;
                }
             }
          break;

      case CF_FNCALL:

          break;

      default:

          if (strcmp(cp->lval,"comment") == 0 || strcmp(cp->lval,"handle") == 0)
             {
             }
          else
             {
             CfOut(cf_error,"","RHS of authorize promise for %s should be a list\n",pp->promiser);
             }
          break;
      }
   }
}
