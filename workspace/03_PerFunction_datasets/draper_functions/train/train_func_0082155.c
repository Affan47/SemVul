compile_massign_opt(rb_iseq_t *iseq, LINK_ANCHOR *ret,
		    NODE *rhsn, NODE *orig_lhsn)
{
    VALUE mem[64];
    const int memsize = numberof(mem);
    int memindex = 0;
    int llen = 0, rlen = 0;
    int i;
    NODE *lhsn = orig_lhsn;

#define MEMORY(v) { \
    int i; \
    if (memindex == memsize) return 0; \
    for (i=0; i<memindex; i++) { \
	if (mem[i] == (v)) return 0; \
    } \
    mem[memindex++] = (v); \
}

    if (rhsn == 0 || nd_type(rhsn) != NODE_ARRAY) {
	return 0;
    }

    while (lhsn) {
	NODE *ln = lhsn->nd_head;
	switch (nd_type(ln)) {
	  case NODE_LASGN:
	    MEMORY(ln->nd_vid);
	    break;
	  case NODE_DASGN:
	  case NODE_DASGN_CURR:
	  case NODE_IASGN:
	  case NODE_IASGN2:
	  case NODE_CVASGN:
	    MEMORY(ln->nd_vid);
	    break;
	  default:
	    return 0;
	}
	lhsn = lhsn->nd_next;
	llen++;
    }

    while (rhsn) {
	if (llen <= rlen) {
	    COMPILE_POPED(ret, "masgn val (popped)", rhsn->nd_head);
	}
	else {
	    COMPILE(ret, "masgn val", rhsn->nd_head);
	}
	rhsn = rhsn->nd_next;
	rlen++;
    }

    if (llen > rlen) {
	for (i=0; i<llen-rlen; i++) {
	    ADD_INSN(ret, nd_line(orig_lhsn), putnil);
	}
    }

    compile_massign_opt_lhs(iseq, ret, orig_lhsn);
    return 1;
}
