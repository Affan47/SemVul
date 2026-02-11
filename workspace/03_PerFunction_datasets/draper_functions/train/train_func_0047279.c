mod_trans FCN((prefix,modno))
outer_char*prefix C0("")
sixteen_bits modno C1("")
{
outer_char HUGE*mod_temp= GET_MEM("mod_temp",NMOD_TEMP,outer_char);
SECT_INFO*ps= sect_info+modno;

if(ps->secno)
{
outer_char c,letter[2];

letter[1]= '\0';

c= (ps->subpage_flag?
XCHR(modno-ps->modno0+'a'-1):'\0');

if(c)
{
if(XORD(c)>'z')
c= '?';
else if(c=='`')
c= '\0';
}

letter[0]= c;


if(
nsprintf(mod_temp,OC("%s %d (sect. %s, p. %d%s)"),5,prefix,modno,ps->secno,ps->pageno,letter)>=(int)(NMOD_TEMP))OVERFLW("mod_temp","");
}
else
{

if(
nsprintf(mod_temp,OC("%s %d"),2,prefix,modno)>=(int)(NMOD_TEMP))OVERFLW("mod_temp","");
}

if(next_mod_name==last_mod_name)

confusion(OC("mod_trans"),OC("too many unfreed mod names"));

return*(next_mod_name++)= mod_temp;
}
