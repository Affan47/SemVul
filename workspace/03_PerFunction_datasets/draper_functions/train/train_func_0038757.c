DeleteAuthList(struct Auth *ap)

{
if (ap != NULL)
   {
   DeleteAuthList(ap->next);
   ap->next = NULL;

   DeleteItemList(ap->accesslist);
   DeleteItemList(ap->maproot);
   free(ap->path);
   free((char *)ap);
   }
}
