stmt_replace_1_by_4(
	struct stmt *block,
	struct stmt *o0,
	struct stmt *n0,
	struct stmt *n1,
	struct stmt *n2,
	struct stmt *n3
)
{
	n0->prev = o0->prev;
	n0->next = n1;
	n1->prev = n0;
	n1->next = n2;
	n2->prev = n1;
	n2->next = n3;
	n3->prev = n2;
	n3->next = o0->next;

	if (n0->prev) {
		n0->prev->next = n0;
	} else {
		block->stmt_first = n0;
	}
	if (n3->next) {
		n3->next->prev = n3;
	} else {
		block->stmt_last = n3;
	}

	stmt_free(o0);
}
