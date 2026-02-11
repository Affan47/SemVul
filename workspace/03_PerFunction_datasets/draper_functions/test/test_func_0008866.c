SeenFunctionProto(char* name,int in_a_function)
{
 if(!(option_xref&XREF_FUNC))
    return;

#if DEBUG
 printf("#Func.c# Function prototype '%s'\n",name);
#endif

 if(!in_a_function)
   {
    if(!prototypes)
       prototypes=NewStringList2();
    AddToStringList2(prototypes,name,parse_file,0,1);
   }
 else
    AddToStringList(cur_func->protos,name,0,1);
}
