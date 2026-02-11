Term_fresh_row_text(int y, int x1, int x2)
{
	int x;

	byte *old_aa = Term->old->a[y];
	wchar_t *old_cc = Term->old->c[y];

	byte *scr_aa = Term->scr->a[y];
	wchar_t *scr_cc = Term->scr->c[y];


	int always_text = Term->always_text;


	int fn = 0;


	int fx = 0;


	byte fa = Term->attr_blank;

	byte oa;
	wchar_t oc;

	byte na;
	wchar_t nc;


	for (x = x1; x <= x2; x++)
	{

		oa = old_aa[x];
		oc = old_cc[x];


		na = scr_aa[x];
		nc = scr_cc[x];


		if ((na == oa) && (nc == oc))
		{

			if (fn)
			{

				if (fa || always_text)
				{
					(void)((*Term->text_hook)(fx, y, fn, fa, &scr_cc[fx]));
				}


				else
				{
					(void)((*Term->wipe_hook)(fx, y, fn));
				}


				fn = 0;
			}


			continue;
		}


		old_aa[x] = na;
		old_cc[x] = nc;


		if (fa != na)
		{

			if (fn)
			{

				if (fa || always_text)
				{
					(void)((*Term->text_hook)(fx, y, fn, fa, &scr_cc[fx]));
				}


				else
				{
					(void)((*Term->wipe_hook)(fx, y, fn));
				}


				fn = 0;
			}


			fa = na;
		}


		if (fn++ == 0) fx = x;
	}


	if (fn)
	{

		if (fa || always_text)
		{
			(void)((*Term->text_hook)(fx, y, fn, fa, &scr_cc[fx]));
		}


		else
		{
			(void)((*Term->wipe_hook)(fx, y, fn));
		}
	}
}
