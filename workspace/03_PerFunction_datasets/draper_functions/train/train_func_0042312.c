OutputCleanActions(struct __ecereNameSpace__ecere__com__Instance * f, char * name, int parts)
{
if(parts > 1)
{
int c;

for(c = 0; c < parts; c++)
__ecereMethod___ecereNameSpace__ecere__sys__File_Printf(f, "\t$(call rmq,$(_%s%d))\n", name, c + 1);
}
else
__ecereMethod___ecereNameSpace__ecere__sys__File_Printf(f, "\t$(call rmq,$(_%s))\n", name);
}
