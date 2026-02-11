Divide(word *R, word *Q, word *T, const word *A, size_t NA, const word *B, size_t NB)
{
	assert(NA && NB && NA%2==0 && NB%2==0);
	assert(B[NB-1] || B[NB-2]);
	assert(NB <= NA);


	word *const TA=T;
	word *const TB=T+NA+2;
	word *const TP=T+NA+2+NB;


	unsigned shiftWords = (B[NB-1]==0);
	TB[0] = TB[NB-1] = 0;
	CopyWords(TB+shiftWords, B, NB-shiftWords);
	unsigned shiftBits = WORD_BITS - BitPrecision(TB[NB-1]);
	assert(shiftBits < WORD_BITS);
	ShiftWordsLeftByBits(TB, NB, shiftBits);


	TA[0] = TA[NA] = TA[NA+1] = 0;
	CopyWords(TA+shiftWords, A, NA);
	ShiftWordsLeftByBits(TA, NA+2, shiftBits);

	if (TA[NA+1]==0 && TA[NA] <= 1)
	{
		Q[NA-NB+1] = Q[NA-NB] = 0;
		while (TA[NA] || Compare(TA+NA-NB, TB, NB) >= 0)
		{
			TA[NA] -= Subtract(TA+NA-NB, TA+NA-NB, TB, NB);
			++Q[NA-NB];
		}
	}
	else
	{
		NA+=2;
		assert(Compare(TA+NA-NB, TB, NB) < 0);
	}

	word BT[2];
	BT[0] = TB[NB-2] + 1;
	BT[1] = TB[NB-1] + (BT[0]==0);


	for (size_t i=NA-2; i>=NB; i-=2)
	{
		AtomicDivide(Q+i-NB, TA+i-2, BT);
		CorrectQuotientEstimate(TA+i-NB, TP, Q+i-NB, TB, NB);
	}


	CopyWords(R, TA+shiftWords, NB);
	ShiftWordsRightByBits(R, NB, shiftBits);
}
