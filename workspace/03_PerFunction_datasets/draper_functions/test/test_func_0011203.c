matchcompext(char *s)
{
 struct extnode *p;
 size_t sl;

 p=compexts;
 sl=strlen(s);

 while(p!=NULL)
   {
    if(sl >= strlen(p->ext))
      {
	if(extcasesens)
	  {
            if(strcmp(s+sl-strlen(p->ext),p->ext)==0) return 1;
	  }
	else
	  {
            if(strcasecmp(s+sl-strlen(p->ext),p->ext)==0) return 1;
	  }
      }
     p=p->next;
   }

 if(namecmp_ext(s)==0) return 1;

 return 0;
}
