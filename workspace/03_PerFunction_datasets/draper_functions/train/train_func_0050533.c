rommon_var_get(struct rommon_var_list *rvl,char *name,
                   char *buffer,size_t len)
{
   struct rommon_var *var;

   if (!(var = rommon_var_find(rvl,name)) || !var->value)
      return(-1);

   strncpy(buffer,var->value,len-1);
   buffer[len-1] = '\0';
   return(0);
}
