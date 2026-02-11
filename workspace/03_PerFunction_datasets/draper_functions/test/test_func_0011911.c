pstack_erase()
{
	while (!pstack.empty()) {
		position p = pstack.top();
		if (p == Superscript) {
			MoveDown();
		} else if (p == Subscript) {
			MoveUp();
		}
#ifdef DEBUG
		if (p == Superscript)
			printf("\tcleared Superscript from position stack\n");
		else if (p == Subscript)
			printf("\tcleared Subscript from position stack\n");
#endif
		pstack.pop();
	}
}
