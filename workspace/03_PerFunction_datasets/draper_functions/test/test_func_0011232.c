search_by_id(void)
{
	char id[11];
	long index;

	printf("ID to search for? ");

	clear_stream();
	scanf("%[a-zA-Z0-9]", id);

	index = find_index_by_id(id);
	if (!index)
		printf("Book not found\n");
	else {
		printf("Title : %s\n",    db.arr[index].title);
		printf("Author: %s %s\n", db.arr[index].authors[0].first,
								  db.arr[index].authors[0].last);
		printf("Year  : %d\n",    db.arr[index].yearPublished);
	}
}
