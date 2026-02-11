pselect_add(FileOfs start, FileOfs end)
{
	bool downward = (start<end);
	if (end<start) {
		FileOfs temp=start;
		start=end;
		end=temp;
	}
	if ((end==sel_start) && !downward) {
		sel_start=start;
	} else if ((start==sel_end) && downward) {
		sel_end=end;
	} else if ((end==sel_end) && !downward) {
		sel_end=start;
	} else if ((start==sel_start) && downward) {
		sel_start=end;
	} else {
		sel_start=start;
		sel_end=end;
	}
	if (sel_start>sel_end) {
		FileOfs temp=sel_start;
		sel_start=sel_end;
		sel_end=temp;
	}
}
