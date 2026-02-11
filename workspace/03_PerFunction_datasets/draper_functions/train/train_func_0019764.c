lt_symbol_alias(struct lt_trace *lt, const char *existing_name, const char *alias, int msb, int lsb)
{
struct lt_symbol *s, *sa;
int len;
int bitlen;
int flagcnt;

if((!lt)||(!existing_name)||(!alias)||(!(s=lt_symfind(lt, existing_name)))||(lt_symfind(lt, alias))) return (NULL);

if(lt->sorted_facs) return(NULL);

while(s->aliased_to)
	{
	s=s->aliased_to;
	}

flagcnt = ((s->flags&LT_SYM_F_INTEGER)!=0) + ((s->flags&LT_SYM_F_DOUBLE)!=0) + ((s->flags&LT_SYM_F_STRING)!=0);
bitlen = (msb<lsb) ? (lsb-msb+1) : (msb-lsb+1);
if((!flagcnt)&&(bitlen!=s->len)) return(NULL);

sa=lt_symadd(lt, alias, lt_hash(alias));
sa->flags = LT_SYM_F_ALIAS;
sa->aliased_to = s;

if(!flagcnt)
	{
	sa->msb = msb;
	sa->lsb = lsb;
	sa->len = bitlen;
	}

sa->symchain = lt->symchain;
lt->symchain = sa;
lt->numfacs++;
if((len=strlen(alias)) > lt->longestname) lt->longestname = len;
lt->numfacbytes += (len+1);

return(sa);
}
