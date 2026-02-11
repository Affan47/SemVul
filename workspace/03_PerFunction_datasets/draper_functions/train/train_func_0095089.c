SplitIdent (ident,chaine)
char *chaine;
char *ident;
{
char idtmp[30],reste[30], *cpt;
int i,j =0,k =0, flag1=0,flag2=0;
   cpt = ident;
   for (i = strlen(ident); i >0; i--)
   {
       if (flag1 == 0)
       {
           if (isspace(*cpt) == 0  &&  *cpt != '(' )
	   {
               flag2 = 1;
               idtmp[j++] = *cpt;
           }
           else
	   {
	     if (flag2 ==  1 )
	     {
	      flag1      = 1;
	      if (*cpt  == '(')  reste[k++] = *cpt;
	     }
	     else idtmp[j++] = *cpt;
           }
       }
       else
       {
            reste[k++] = *cpt;
       }
       cpt ++;
   }
   idtmp[j] = '\0';
   reste[k] = '\0';
   strcpy (chaine,reste);
   strcpy (ident,idtmp);
}
