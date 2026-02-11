dump_toolbar_items(const toolbar_item_t *items)
{
	while(items)
	{
	        if(items->id)
			printf("   BUTTON %d", items->id );
		else
	      		printf("   SEPARATOR");

		printf("\n");

		items = items->next;
	}
}
