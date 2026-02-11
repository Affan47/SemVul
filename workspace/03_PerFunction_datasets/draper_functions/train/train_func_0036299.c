Subst(const char *txt, const subst_t *s)
{
   xstring buf("");

   char str[3];
   bool last_subst_empty=true;

   while(*txt)
   {
      char ch = *txt++;
      const char *to_add = NULL;
      if(ch=='\\' && *txt && *txt!='\\')
      {
	 ch=*txt++;
	 if(ch >= '0' && ch < '8') {
	    unsigned len;
	    unsigned code;
	    txt--;
	    if(sscanf(txt,"%3o%n",&code,&len)!=1)
	       continue;
	    ch=code;
	    txt+=len;
	    str[0]=ch;
	    str[1]=0;
	    to_add=str;
	 } else {
	    if(ch=='?')
	    {
	       if(last_subst_empty)
		  txt++;
	       to_add="";
	    }
	    for(int i = 0; s[i].from; i++) {
	       if(s[i].from != ch)
		  continue;
	       to_add=s[i].to;
	       if(!to_add)
		  to_add = "";
	       last_subst_empty = (*to_add==0);
	    }
	    if(!to_add) {
	       str[0]='\\';
	       str[1]=ch;
	       str[2]=0;
	       to_add=str;
	    }
	 }
      }
      else
      {
	 if(ch=='\\' && *txt=='\\')
	    txt++;
	 str[0]=ch;
	 str[1]=0;
	 to_add=str;
      }

      if(to_add==0)
	 continue;

      buf.append(to_add);
   }
   return(buf.borrow());
}
