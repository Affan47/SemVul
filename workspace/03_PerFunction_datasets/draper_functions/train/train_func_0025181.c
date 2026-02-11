stmt_replace_1_by_6(
	struct stmt *block,
	struct stmt *o0,
	struct stmt *n0,
	struct stmt *n1,
	struct stmt *n2,
	struct stmt *n3,
	struct stmt *n4,
	struct stmt *n5
)
{
	n0->prev = o0->prev;
	n0->next = n1;
	n1->prev = n0;
	n1->next = n2;
	n2->prev = n1;
	n2->next = n3;
	n3->prev = n2;
	n3->next = n4;
	n4->prev = n3;
	n4->next = n5;
	n5->prev = n4;
	n5->next = o0->next;

	if (n0->prev) {
		n0->prev->next = n0;
	} else {
		block->stmt_first = n0;
	}
	if (n5->next) {
		n5->next->prev = n5;
	} else {
		block->stmt_last = n5;
	}

	stmt_free(o0);
}
