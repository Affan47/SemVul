er_paramutils_print_key_desc
(const char *flag_prefix, const char *keyword, const char *description)

{
int i, ii, tab = COMMENT_TAB_POSITION;

char *mystr, *ptr, *mykeyword;


ER_TRACE(__func__)


mystr = (char *) cpl_malloc((size_t) SIZE_X);
if (mystr == NULL)
   {
   cpl_msg_warning (er_func,
            "Could not allocate initial %d bytes for help description",
            SIZE_X);
   return;
   }


i = (int) strlen(flag_prefix);
ii = (int) strlen(keyword);
if ((i+ii) > (SIZE_X-4))
   {
   cpl_msg_warning (er_func,
                    "Size of keyword (= %d) too large - will be truncated...",ii);
   mykeyword = (char *) cpl_malloc((size_t) SIZE_X);
   (void) strncpy(mykeyword,keyword,(SIZE_X-6));
   mykeyword[SIZE_X-6] = '\0';
   }
else
   mykeyword = (char *) keyword;

i = sprintf(mystr,"  %s%s",flag_prefix,mykeyword);
if (tab < i) tab = i + 2;


ptr = mystr + i;
for (ii = i; ii < tab; ii++) *ptr++ = ' ';
*ptr++ = ':';
*ptr++ = ' ';
*ptr = '\0';
tab += 2;


i = tab + (int) strlen(description) + 2;
if (i > SIZE_X)
   {
   er_enlarge("paramutils_print_key_desc",&mystr,i);
   }
(void) strcpy(mystr+tab, description);


(void) printf ("%s\n",er_strutils_split(mystr,tab,er_strutils_termwidth()));

cpl_free(mystr);
}
