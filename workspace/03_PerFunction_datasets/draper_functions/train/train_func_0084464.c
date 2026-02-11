SeenFunctionCall(char* name)
{
 if(!(option_xref&XREF_FUNC))
    return;

#if DEBUG
 printf("#Func.c# Function call for '%s()' in %s()\n",name,cur_func->name);
#endif

 AddToStringList2(cur_func->calls,name,NULL,1,1);
}
