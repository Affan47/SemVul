mdb_sql_dump_node(MdbSargNode *node, int level)
{
	int i;
	int mylevel = level+1;

	if (!level)
		printf("root  ");
	for (i=0;i<mylevel;i++) printf("--->");
	switch (node->op) {
		case MDB_OR:
			printf(" or\n");
			break;
		case MDB_AND:
			printf(" and\n");
			break;
		case MDB_NOT:
			printf(" not\n");
			break;
		case MDB_LT:
			printf(" < %d\n", node->value.i);
			break;
		case MDB_GT:
			printf(" < %d\n", node->value.i);
			break;
		case MDB_LIKE:
			printf(" like %s\n", node->value.s);
			break;
		case MDB_EQUAL:
			printf(" = %d\n", node->value.i);
			break;
	}
	if (node->left) {
		printf("left  ");
		mdb_sql_dump_node(node->left, mylevel);
	}
	if (node->right) {
		printf("right ");
		mdb_sql_dump_node(node->right, mylevel);
	}
}
