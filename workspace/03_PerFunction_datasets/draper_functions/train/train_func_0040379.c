OutputFile(File file)
{
 int i;
 Include inc;
 Function func;
 Variable var;
 Typedef type;

 printf("File: %s\n\n",file->name);

 for(inc=file->includes,i=0;inc;inc=inc->next,i++)
   {
    printf("    %s %c%s%c\n",i?"          ":"Includes: ",inc->scope==GLOBAL?'<':'"',inc->name,inc->scope==GLOBAL?'>':'"');
    OutputInclude(inc,1);
   }
 if(file->includes)
    printf("\n");

 for(func=file->functions,i=0;func;func=func->next,i++)
    printf("    %s %s\n",i?"          ":"Functions:",func->name);
 if(file->functions)
    printf("\n");

 for(var=file->variables,i=0;var;var=var->next,i++)
    printf("    %s %s\n",i?"          ":"Variables:",var->name);
 if(file->variables)
    printf("\n");

 for(type=file->typedefs,i=0;type;type=type->next,i++)
    printf("    %s %s\n",i?"          ":"Types:    ",type->name);
 if(file->typedefs)
    printf("\n");

 if(option_xref&XREF_FILE)
   {
    for(i=0;i<file->inc_in->n;i++)
       printf("   %s %s\n",i?"            ":"Included in:",file->inc_in->s[i]);
    if(file->inc_in->n)
       printf("\n");
   }

 if(option_xref&XREF_FUNC)
   {
    for(i=0;i<file->f_refs->n;i++)
       printf("   %s %s : %s\n",i?"            ":"Refs func:  ",file->f_refs->s1[i],file->f_refs->s2[i]);
    if(file->f_refs->n)
       printf("\n");
   }

 if(option_xref&XREF_VAR)
   {
    for(i=0;i<file->v_refs->n;i++)
       printf("   %s %s : %s\n",i?"            ":"Refs var:   ",file->v_refs->s1[i],file->v_refs->s2[i]);
    if(file->v_refs->n)
       printf("\n");
   }
}
