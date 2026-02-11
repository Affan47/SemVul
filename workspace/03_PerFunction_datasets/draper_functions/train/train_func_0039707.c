get_record(const char *name)
{
   int id,n;
   if(sscanf(name,"%d%n",&id,&n)==1 && !name[n])
      return new IdNamePair(id,name);
   return 0;
}
