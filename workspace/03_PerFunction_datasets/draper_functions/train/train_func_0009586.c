CopyLabel(char *label, char *buf, int bufSize)
{
   struct list_head *p;
   LabelRecord *pl;
   int i=0, found=0;


   list_for_each(p, &head.list)
   {
      pl = list_entry(p, LabelRecord, list);
      if (strcasecmp(pl->name, label) == 0)
      {
         found = 1;
         break;
      }
   }

   if (!found)
   {
      BUG("error undefined label %s\n", label);
      goto bugout;
   }

   if (pl->valueSize > bufSize)
   {
      BUG("error label %s size=%d buf=%d\n", label, pl->valueSize, bufSize);
      goto bugout;
   }

   memcpy(buf, pl->value, pl->valueSize);
   i=pl->valueSize;

bugout:
   return i;
}
