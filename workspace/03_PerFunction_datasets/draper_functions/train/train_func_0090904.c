find_constval(constvalue * table, char *name, short idx)
{
   constvalue         *ptr = table->next;

   while (ptr)
     {
	if (strcmp(name, ptr->name) == 0 && ptr->index == idx)
	   return ptr;
	ptr = ptr->next;
     }
   return NULL;
}
