ListColumns(void)
{
	COLUMN **	columnPtr;
	const COLUMN *	column;

	printf("Column Name          Displayed As    Width\n");
	printf("-----------          ------------    -----\n");

	for (columnPtr = columnTable; *columnPtr; columnPtr++)
	{
		column = *columnPtr;

		printf("%-20s %-15s %3d\n", column->name, column->heading,
			column->width);
	}

	printf("\n");
	printf("Note: Column names may be abbreviated.  They are used in\n");
	printf("several ways: displaying, sorting, and for the cond option.\n");
}
