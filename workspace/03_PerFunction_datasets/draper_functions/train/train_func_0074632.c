do_match(Var arglist, int reverse)
{
    const char *subject, *pattern;
    int i;
    Pattern pat;
    Var ans;
    Match_Indices regs[10];

    subject = arglist.v.list[1].v.str;
    pattern = arglist.v.list[2].v.str;
    pat = get_pattern(pattern, (arglist.v.list[0].v.num == 3
				&& is_true(arglist.v.list[3])));

    if (!pat.ptr) {
	ans.type = TYPE_ERR;
	ans.v.err = E_INVARG;
    } else
	switch (match_pattern(pat, subject, regs, reverse)) {
	case MATCH_SUCCEEDED:
	    ans = new_list(4);
	    ans.v.list[1].type = TYPE_INT;
	    ans.v.list[2].type = TYPE_INT;
	    ans.v.list[4].type = TYPE_STR;
	    ans.v.list[1].v.num = regs[0].start;
	    ans.v.list[2].v.num = regs[0].end;
	    ans.v.list[3] = new_list(9);
	    ans.v.list[4].v.str = str_ref(subject);
	    for (i = 1; i <= 9; i++) {
		ans.v.list[3].v.list[i] = new_list(2);
		ans.v.list[3].v.list[i].v.list[1].type = TYPE_INT;
		ans.v.list[3].v.list[i].v.list[1].v.num = regs[i].start;
		ans.v.list[3].v.list[i].v.list[2].type = TYPE_INT;
		ans.v.list[3].v.list[i].v.list[2].v.num = regs[i].end;
	    }
	    break;
	case MATCH_FAILED:
	    ans = new_list(0);
	    break;
	case MATCH_ABORTED:
	    ans.type = TYPE_ERR;
	    ans.v.err = E_QUOTA;
	    break;
	}

    return ans;
}
