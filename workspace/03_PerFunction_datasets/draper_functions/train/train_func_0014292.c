IncrementCounter(struct Item **list,char *name)

{
if (!IsItemIn(*list,name))
   {
   AppendItem(list,name,"");
   IncrementItemListCounter(*list,name);
   }
else
   {
   IncrementItemListCounter(*list,name);
   }
}
