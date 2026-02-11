__ecereMethod___ecereNameSpace__ecere__sys__MinMaxValue_OnGetDataFromString(struct __ecereNameSpace__ecere__com__Class * class, int * this, char * string)
{
if(!(strcasecmp)(string, "Inf"))
(*this) = (((int)0x7fffffff));
else if(!(strcasecmp)(string, "-Inf"))
(*this) = (((int)0x80000000));
else
(*this) = strtol(string, (((void *)0)), 0);
return 0x1;
}
