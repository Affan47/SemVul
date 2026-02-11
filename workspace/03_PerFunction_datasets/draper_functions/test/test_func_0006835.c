merge2defines(file1, file2)
   struct inclist   *file1;
   struct inclist   *file2;
{
   if ((file1!=NULL) && (file2!=NULL))
        {
      int first1 = 0;
      int last1 = file1->i_ndefs - 1;

      int first2 = 0;
      int last2 = file2->i_ndefs - 1;

                int first=0;
                struct symtab** i_defs = NULL;
      int deflen=file1->i_ndefs+file2->i_ndefs;

                if (deflen>0)
                {

                   deflen += (SYMTABINC - deflen % SYMTABINC) % SYMTABINC;
                   i_defs=(struct symtab**)
             malloc(deflen*sizeof(struct symtab*));
                   if (i_defs==NULL) return 0;
           }

           while ((last1 >= first1) && (last2 >= first2))
           {
             char *s1=file1->i_defs[first1]->s_name;
             char *s2=file2->i_defs[first2]->s_name;

              if (strcmp(s1,s2) < 0)
                           i_defs[first++]=file1->i_defs[first1++];
              else if (strcmp(s1,s2) > 0)
                           i_defs[first++]=file2->i_defs[first2++];
                        else
                        {
                           i_defs[first++]=file2->i_defs[first2++];
                                first1++;
                        }
           }
           while (last1 >= first1)
           {
                        i_defs[first++]=file1->i_defs[first1++];
           }
           while (last2 >= first2)
           {
                        i_defs[first++]=file2->i_defs[first2++];
           }

                if (file1->i_defs) free(file1->i_defs);
                file1->i_defs=i_defs;
                file1->i_ndefs=first;

      return 1;
     }
   return 0;
}
