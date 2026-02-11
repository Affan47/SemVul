add_deftag(char *catg, char *tag)
{
   int         ii, cc, cc1, cc2;
   char        tag1[tagcc], tag2[tagcc];
   char        *pp1, *pp2;

   strncpy0(tag1,tag,tagcc);
   cc = strTrim2(tag2,tag1);
   if (! cc) return 4;

   if (utf8_check(tag2)) {
      printf("bad utf8 characters: %s \n",tag2);
      return 3;
   }

   while ((pp1 = strpbrk(tag2,tagdelims":"))) *pp1 = '-';

   strcpy(tag,tag2);

   del_deftag(tag);

   if (! catg || *catg <= ' ') catg = (char *) "nocatg";

   cc1 = strlen(catg);

   for (ii = 0; ii < maxtagcats; ii++)
   {
      pp1 = tags_deftags[ii];
      if (! pp1) goto newcatg;
      if (! strnEqu(catg,pp1,cc1)) continue;
      if (pp1[cc1] == ':') goto oldcatg;
   }

newcatg:
   if (ii == maxtagcats) goto toomanycats;
   cc1 = strlen(catg) + strlen(tag) + 6;
   pp1 = zmalloc(cc1,"deftags");
   *pp1 = 0;
   strncatv(pp1,cc1,catg,": ",tag,tagdelim2,null);
   tags_deftags[ii] = tags_deftags[ii-1];
   tags_deftags[ii-1] = pp1;
   return 0;

oldcatg:
   cc1 = strlen(tag);
   pp2 = pp1 + 2;
   while (true) {
      pp2 = strcasestr(pp2,tag);
      if (! pp2) break;
      if (strchr(tagdelims,pp2[cc]) && strchr(tagdelims":", pp2[-2]))
         return 1;
      pp2 += cc1;
   }
   cc2 = strlen(pp1);
   if (cc1 + cc2 + 4 > tagGcc) goto cattoobig;
   pp2 = strdupz(pp1,cc2+4,"def_tags");
   zfree(pp1);
   tags_deftags[ii] = pp2;
   strcpy(pp2+cc2,tag);
   strcpy(pp2+cc2+cc1,tagdelim2);
   return 0;

toomanycats:
   zmessLogACK(mWin,"more than %d categories",maxtagcats);
   return 2;

cattoobig:
   zmessLogACK(mWin,"category is too big");
   return 2;
}
