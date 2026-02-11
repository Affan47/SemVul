PrintNodes() {
	fwprintf(trace, L"Graph nodes:\n");
	fwprintf(trace, L"----------------------------------------------------\n");
	fwprintf(trace, L"   n type name          next  down   sub   pos  line\n");
	fwprintf(trace, L"                               val  code\n");
	fwprintf(trace, L"----------------------------------------------------\n");

	Node *p;
	for (int i=0; i<nodes->Count; i++) {
		p = (Node*)((*nodes)[i]);
		fwprintf(trace, L"%4d %ls ", p->n, (nTyp[p->typ]));
		if (p->sym != NULL) {
			wchar_t *paddedName = Name(p->sym->name);
			fwprintf(trace, L"%12s ", paddedName);
			coco_string_delete(paddedName);
		} else if (p->typ == Node::clas) {
			CharClass *c = (CharClass*)(*classes)[p->val];
			wchar_t *paddedName = Name(c->name);
			fwprintf(trace, L"%12s ", paddedName);
			coco_string_delete(paddedName);
		} else fwprintf(trace, L"             ");
		fwprintf(trace, L"%5d ", Ptr(p->next, p->up));

		if (p->typ == Node::t || p->typ == Node::nt || p->typ == Node::wt) {
			fwprintf(trace, L"             %5s", Pos(p->pos));
		} if (p->typ == Node::chr) {
			fwprintf(trace, L"%5d %5d       ", p->val, p->code);
		} if (p->typ == Node::clas) {
			fwprintf(trace, L"      %5d       ", p->code);
		} if (p->typ == Node::alt || p->typ == Node::iter || p->typ == Node::opt) {
			fwprintf(trace, L"%5d %5d       ", Ptr(p->down, false), Ptr(p->sub, false));
		} if (p->typ == Node::sem) {
			fwprintf(trace, L"             %5s", Pos(p->pos));
		} if (p->typ == Node::eps || p->typ == Node::any || p->typ == Node::sync) {
			fwprintf(trace, L"                  ");
		}
		fwprintf(trace, L"%5d\n", p->line);
	}
	fwprintf(trace, L"\n");
}
