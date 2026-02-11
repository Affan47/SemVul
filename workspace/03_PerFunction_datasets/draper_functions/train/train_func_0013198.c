search_by_id(void)
{
	long id;
	int way;
	long index;
	Book *B;

	printf("ID to search for? ");
	clear_stream();
	scanf("%ld", &id);

	printf("Which way to search? [1-linear 2-binary 3-interpolation] ");
	clear_stream();
	scanf("%d", &way);

	switch(way) {
		case 1:
			index = find_index_by_id(id);
			break;
		case 2:
		case 3:

			if (!sorted) {
				printf("Sorting...\n");
				sort_db();
				sorted = 1;
			}

			index = btraverse(id, way - 1);
			break;
		default:
			printf("Wrong answer\n");
			return;
	}

	if (index == -1) {
		printf("Book not found\n");
		return;
	}
	B = &db.arr[index];

	printf("Title : %s\n",    B->title);
	printf("Author: %s %s\n", B->authors[0].first, B->authors[0].last);
	printf("Year  : %d\n",    B->yearPublished);
}
