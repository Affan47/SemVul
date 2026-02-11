AddAuthHostItem(char *path,char *attribute,char *classes,struct Auth **list)

{ char varbuff[CF_EXPANDSIZE];
  struct Auth *ptr;
  struct Item *ip, *split = NULL;

Debug1("AddAuthHostItem(%s,%s)\n",path,attribute);

if (!IsDefinedClass(CLASSBUFF))
   {
   Debug1("Not installing AuthItem no match\n");
   return;
   }

split = SplitStringAsItemList(attribute,LISTSEPARATOR);

for (ptr = *list; ptr != NULL; ptr=ptr->next)
   {
   ExpandVarstring(path,varbuff,"");

   if (strcmp(ptr->path,varbuff) == 0)
      {
      for (ip = split; ip != NULL; ip=ip->next)
         {
         if (!HandleAdmitAttribute(ptr,ip->name))
            {
            PrependItem(&(ptr->accesslist),ip->name,classes);
            }
         }

      DeleteItemList(split);
      return;
      }
   }

DeleteItemList(split);
}
