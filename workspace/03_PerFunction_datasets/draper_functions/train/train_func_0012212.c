TraiterChaine (chaine,traite)
char * chaine;
struct alpha_num *traite;
{
char *cpt;
int i=0,j=0,k=0,l=0,flag=0,f=0;

   KillEsp(chaine);

   if ( *chaine == '(')
   {
     f = 1;
     chaine++;
   }

   cpt = chaine;
   for (i = strlen(chaine); i >0; i--)
   {
     switch (flag)
     {
      case 0:
      {
          if (isdigit(*cpt) )
              traite->gauche[j++] = *cpt;
          if (isalpha (*cpt))
	  {
              traite->alpha[k++] = *cpt;
              flag = 1;
          }
	  if (*cpt == ')' && f == 0)
	    Erreur ("BIT descriptor error");
          break;
      }
      case 1:
      {
          if (isalpha (*cpt))
	  {
              traite->alpha[k++] = *cpt;
              flag = 1;
	      break;
          }
	  if (isdigit(*cpt))
	  {
	     traite->droite[l++] = *cpt;
	     flag = 2;
	     break;
	  }
	  if ( ! ( (*cpt == ')') && (f==1) && (i==1) ) )
	      Erreur("TraiterChaine : VECTOR field descriptor error");
          break;
      }
      case 2:
      {
          if (isdigit(*cpt))
              traite->droite[l++] = *cpt;
	  else
	     if( ! ( (*cpt == ')') && (f==1) && (i==1) ) )
              Erreur ("TraiterChaine  :VECTOR field descriptor error");
          break;
      }
     }
     cpt++;
   }
   traite->gauche[j] = '\0';
   traite->alpha[k] = '\0';
   traite->droite[l] = '\0';

   return ;
}
