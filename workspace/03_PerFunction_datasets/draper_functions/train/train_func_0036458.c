copytrv(trav1, trav2)
struct trav *trav1, *trav2;
{
	int	i;

	for (i = 0; i<MAXTRAV; ++i) {
		trav2 -> tdest = trav1 -> tdest;
		trav2 -> tverb = trav1 -> tverb;
		trav2 -> tcond = trav1 -> tcond;
	}
}
