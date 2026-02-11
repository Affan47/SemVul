mdb_test_int(MdbSargNode *node, gint32 i)
{
	switch (node->op) {
		case MDB_EQUAL:

			if (node->value.i == i) return 1;
			break;
		case MDB_GT:
			if (node->value.i < i) return 1;
			break;
		case MDB_LT:
			if (node->value.i > i) return 1;
			break;
		case MDB_GTEQ:
			if (node->value.i <= i) return 1;
			break;
		case MDB_LTEQ:
			if (node->value.i >= i) return 1;
			break;
		default:
			fprintf(stderr, "Calling mdb_test_sarg on unknown operator.  Add code to mdb_test_int() for operator %d\n",node->op);
			break;
	}
	return 0;
}
