ellSeg (bend S1l1, bend S1l2, bend T)
{
    if (S1l1 == T) {
	if (S1l2== T) return -1;
	else return 0;
    }
    else return 1;
}
