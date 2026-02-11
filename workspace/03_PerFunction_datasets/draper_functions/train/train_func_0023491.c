get_first_set(const pcre *code, const char *stringname, int *ovector)
#else
static int
get_first_set(const pcre16 *code, PCRE_SPTR16 stringname, int *ovector)
#endif
{
const REAL_PCRE *re = (const REAL_PCRE *)code;
int entrysize;
pcre_uchar *entry;
#ifdef COMPILE_PCRE8
char *first, *last;
#else
PCRE_UCHAR16 *first, *last;
#endif

#ifdef COMPILE_PCRE8
if ((re->options & PCRE_DUPNAMES) == 0 && (re->flags & PCRE_JCHANGED) == 0)
  return pcre_get_stringnumber(code, stringname);
entrysize = pcre_get_stringtable_entries(code, stringname, &first, &last);
#else
if ((re->options & PCRE_DUPNAMES) == 0 && (re->flags & PCRE_JCHANGED) == 0)
  return pcre16_get_stringnumber(code, stringname);
entrysize = pcre16_get_stringtable_entries(code, stringname, &first, &last);
#endif
if (entrysize <= 0) return entrysize;
for (entry = (pcre_uchar *)first; entry <= (pcre_uchar *)last; entry += entrysize)
  {
  int n = GET2(entry, 0);
  if (ovector[n*2] >= 0) return n;
  }
return GET2(entry, 0);
}
