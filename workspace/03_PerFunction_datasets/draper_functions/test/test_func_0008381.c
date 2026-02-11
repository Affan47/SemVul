cycle_in(int num, int next_num, int cnt, int cnt2)
{
	CYCLE_RANGE_PTR	cx, cy;

	cx = cycle_in_in(num);
	cycle_current = cx;

	if (cx == NULL)
		fprintf(fp, "     ");
	else
	{
		if (cx->mul == 0)
			cycle_exclude = TRUE;


		if (cx->cnt2 == 2)
			cycle_alwaystake = TRUE;


		if (cx->val != 0)
		{
			cnt = cx->val;
			fprintf(fp, ";=%2d", cnt);

		}
		else if	(
					(cx->min == cx->max) &&

					(cnt2 != cnt) &&


					(cx -> mul > 1)
					)
		{
			fprintf(fp,";%3d = %d * %dx + %d",
				cnt2 * (cx->mul - 1) + cnt, cnt2, cx->mul - 1, cnt);
			cnt= cnt2 * (cx->mul - 1) + cnt;
			cx->cnt2 = 1;

		}
		else
		{
			cy = cycle_in_in(next_num);

			if (( (cy == NULL) ||

				((cy->min == next_num) && (cy->mul == 0)) ||

				(cycle_alwaystake)

				) &&
				(cnt != cnt2)

				)
			{

				cnt = cnt2;
				fprintf(fp, ";^%2d", cnt);
			}
			else
				fprintf(fp, "; %2d", cnt);
		}

		cx->cnt += cnt;

		if (cycle_exclude)
			fprintf(fp, "-");
		else
			fprintf(fp, " ");
	}

	return;
}
