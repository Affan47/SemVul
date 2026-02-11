SelectGroupMatch(struct stat *lstatptr,struct Rlist *crit)

{ struct AlphaList leafattrib;
  char buffer[CF_SMALLBUF];
  struct group *gr;
  struct Rlist *rp;

InitAlphaList(&leafattrib);

sprintf(buffer,"%d",lstatptr->st_gid);
PrependAlphaList(&leafattrib,buffer);

if ((gr = getgrgid(lstatptr->st_gid)) != NULL)
   {
   PrependAlphaList(&leafattrib,gr->gr_name);
   }
else
   {
   PrependAlphaList(&leafattrib,"none");
   }

for (rp = crit; rp != NULL; rp = rp->next)
   {
   if (EvalFileResult((char *)rp->item,&leafattrib))
      {
      Debug(" - ? Select group match\n");
      DeleteAlphaList(&leafattrib);
      return true;
      }

   if (gr && FullTextMatch((char *)rp->item,gr->gr_name))
      {
      Debug(" - ? Select owner match\n");
      DeleteAlphaList(&leafattrib);
      return true;
      }

   if (FullTextMatch((char *)rp->item,buffer))
      {
      Debug(" - ? Select owner match\n");
      DeleteAlphaList(&leafattrib);
      return true;
      }
   }

DeleteAlphaList(&leafattrib);
return false;
}
