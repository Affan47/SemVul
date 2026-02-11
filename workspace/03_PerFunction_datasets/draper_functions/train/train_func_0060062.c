print_conflicts(state)
int state;
{
    register int symbol, act, number;
    register action *p;

    symbol = -1;
    for (p = parser[state]; p; p = p->next)
    {
	if (p->suppressed == 2)
	    continue;

	if (p->symbol != symbol)
	{
	    symbol = p->symbol;
	    number = p->number;
	    if (p->action_code == SHIFT)
		act = SHIFT;
	    else
		act = REDUCE;
	}
	else if (p->suppressed == 1)
	{
	    if (state == final_state && symbol == 0)
	    {
		fprintf(verbose_file, "%d: shift/reduce conflict \
(accept, reduce %d) on $end\n", state, p->number - 2);
	    }
	    else
	    {
		if (act == SHIFT)
		{
		    fprintf(verbose_file, "%d: shift/reduce conflict \
(shift %d, reduce %d) on %s\n", state, number, p->number - 2,
			    symbol_name[symbol]);
		}
		else
		{
		    fprintf(verbose_file, "%d: reduce/reduce conflict \
(reduce %d, reduce %d) on %s\n", state, number - 2, p->number - 2,
			    symbol_name[symbol]);
		}
	    }
	}
    }
}
