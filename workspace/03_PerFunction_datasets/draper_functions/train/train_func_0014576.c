WriteWarnRawInclude(Include inc)
{
 if(option_raw)
    printf("\nINCLUDES : '%s' [%s file]\n",inc->name,(inc->scope==GLOBAL?"System":"Local"));

 if(inc->comment && option_raw)
    printf("<<<\n%s\n>>>\n",inc->comment);
 if(option_warn&WARN_COMMENT && !inc->comment)
    printf("Warning %16s : #Include '%s' does not have a comment.\n",filename,inc->name);

 if(option_raw && inc->includes)
    WriteWarnRawSubInclude(inc->includes,1);
}
