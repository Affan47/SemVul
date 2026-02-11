SeenFunctionArg(char* name,char *type)
{
#if DEBUG
 printf("#Func.c# Function arg %s '%s' in %s()\n",name?name:"K&R",type?type:"K&R",cur_func->name);
#endif

 if(name)
   {
    if(type && strcmp(type,"void"))
      {
       int i;

       for(i=0;i<cur_func->args->n;i++)
          if(!strcmp(cur_func->args->s1[i],name))
            {
             Free(cur_func->args->s1[i]);
             cur_func->args->s1[i]=MallocString(type);
             cur_func->args->s2[i]=MallocString(SplitComment(&cur_func->comment,type));
             break;
            }
       if(i==cur_func->args->n)
          AddToStringList2(cur_func->args,type,SplitComment(&cur_func->comment,type),0,0);

       if(!cur_func->args->s2[i])
          cur_func->args->s2[i]=MallocString(GetCurrentComment());
      }
    else
       AddToStringList2(cur_func->args,name,NULL,0,0);
   }
}
