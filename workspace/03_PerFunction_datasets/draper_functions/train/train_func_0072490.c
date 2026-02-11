_bt_checksplitloc(FindSplitData *state, OffsetNumber firstright,
				  int leftfree, int rightfree,
				  bool newitemonleft, Size firstrightitemsz)
{


	if (newitemonleft)
		leftfree -= (int) state->newitemsz;
	else
		rightfree -= (int) state->newitemsz;


	if (!state->is_leaf)
		rightfree += (int) firstrightitemsz -
			(int) (MAXALIGN(sizeof(IndexTupleData)) + sizeof(ItemIdData));


	if (leftfree >= 0 && rightfree >= 0)
	{
		int			delta;

		if (state->is_rightmost)
		{


			delta = (state->fillfactor * leftfree)
				- ((100 - state->fillfactor) * rightfree);
		}
		else
		{

			delta = leftfree - rightfree;
		}

		if (delta < 0)
			delta = -delta;
		if (!state->have_split || delta < state->best_delta)
		{
			state->have_split = true;
			state->newitemonleft = newitemonleft;
			state->firstright = firstright;
			state->best_delta = delta;
		}
	}
}
