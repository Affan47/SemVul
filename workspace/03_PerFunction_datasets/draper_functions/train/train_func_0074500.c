cycle_end(int num)
{
	CYCLE_RANGE_PTR	cr, cx;
	int	cycles;

	cr = cycle_current;

	while (cr != NULL)
	{
		if (num > cr->max)
		{
			if (cr->val == 0)

			{
				if	(
					(cr->min == cr->max) &&

					(cr->cnt2 == 1) &&

					(cr->val == 0) &&

					(cr->mul > 1))
				{
					cycles = cr->cnt;

				}
				else
				{
					cycles = cr->cnt;

					if (!newline)
						fprintf(fp, "\n;");

					fprintf(fp, "\n; --- Cycle count %04x-%04x = %d",
						cr->min, cr->max, cycles);

					if (cr->mul > 1)
					{
						cycles *= cr->mul;
						fprintf(fp, " * %dx = %d", cr->mul, cycles);
					}

					if (cr->mul == 0)
					{
						fprintf(fp, " - not included to the parent cycle count.");
						cycles = 0;
					}

					fprintf(fp, "\n;");
					newline = TRUE;
				}
			}
			else
				cycles = cr->val;

			if (cr->mul == 0)
				cycle_exclude = FALSE;

			if (cr->cnt2 == 2)
				cycle_alwaystake = FALSE;

			cx = cr->parent;

			if (cx != NULL)
				cx->cnt += cycles;

			cr->cnt = 0;
			cr = cx;
		}
		else
			cr = NULL;
	}
}
