match_hier_name(struct xpndfile_t *xfp_hd, char *name)
{
 char *cp, *last;
 char str[RECLEN];
 struct xpndfile_t *xfp;


 if (name[0] == '.' && name[1] == '/') name += 2;
 last = name;
 xfp = xfp_hd;
 cp = strchr(name, '/');
 if (cp == NULL)
  {

   if (xfp->xpfnxt == NULL && match_wildcard_str(name, xfp)) return(TRUE);

   else if (xfp->wildcard == HIER && xfp->xpfnxt->xpfnxt == NULL
    && match_wildcard_str(name, xfp->xpfnxt)) return(TRUE);
  }
 else
  {
   for (; xfp != NULL && cp != NULL; cp = strchr(cp, '/'))
    {


     strncpy(str, last, cp - last);
     str[cp-last] ='\0';

     if (!match_wildcard_str(str, xfp)) return(FALSE);

     if (xfp->wildcard == HIER)
      {

       if (xfp->xpfnxt == NULL) return(TRUE);


hier:
       xfp = xfp->xpfnxt;
       for (; cp != NULL;  )
        {

         if ((cp - last) == 0) strcpy(str, cp);
         else
          {
           strncpy(str, last, cp - last);
           str[cp-last] ='\0';
          }

         if (match_wildcard_str(str, xfp))
          {
           xfp = xfp->xpfnxt;
           if (xfp == NULL) return(TRUE);
          }
         last = ++cp;

         if ((cp = strchr(cp, '/')) == NULL)
          {

           if (xfp->xpfnxt != NULL) return(FALSE); strcpy(str, last);

           if (match_wildcard_str(str, xfp)) return(TRUE);
          }
        }
      }
     last = ++cp;


     if (xfp->incall && strchr(cp, '/') == NULL) return(TRUE);


     xfp = xfp->xpfnxt;
     if (xfp == NULL)  return(FALSE);
     if (xfp->wildcard == HIER && xfp->xpfnxt != NULL) goto hier;

     if (*cp != '\0' && strchr(cp, '/') == NULL)
      {
       if (xfp->xpfnxt == NULL && match_wildcard_str(cp, xfp)) return(TRUE);
       else return(FALSE);
      }
    }
  }
 return(FALSE);
}
