overflow FCN((s,abbrev))
CONST outer_char s[]C0("Condition that caused overflow.")
CONST outer_char abbrev[]C1("Abbreviation for buffer.")
{
if(*abbrev=='\0')
{

fatal(ERR_NULL,OC("!!! Sorry, CAPACITY EXCEEDED:  "),OC("%s contents too long."),(char*)s);
}
else
{
MEM HUGE*m= msearch(abbrev,0L);


fatal(ERR_NULL,OC("!!! Sorry, CAPACITY EXCEEDED:  "),OC("Too many %s.  Current number is %lu, absolute max is \
%lu.  Use command-line option \"-y%s...\" to override default."),(char*)s,m->nunits,m->max,(char*)abbrev);
}
}
