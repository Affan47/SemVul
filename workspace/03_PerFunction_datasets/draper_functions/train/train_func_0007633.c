find_asmrule_match(char *asmrule,int **matched,int bw)
{
    int i;
    int rules;
    int matchedrules = 0;

    rules = count_rules(asmrule);

    *matched = (int *)xmalloc(sizeof(int) * rules);

    for(i = 0; i < rules ;i++) {

	if(asmrule_match(asmrule,bw)) {
	    display(MSDL_DBG,"rule[%d] = %d matched\n",matchedrules,i);
	    (*matched)[matchedrules] = i;
	    matchedrules++;
	}
	asmrule = next_rule(asmrule);
    }

    return matchedrules;
}
