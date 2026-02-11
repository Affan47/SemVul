Coefficients_27_39 P3((LARpp_j_1, LARpp_j, LARp),
	register word * LARpp_j_1,
	register word * LARpp_j,
	register word * LARp)
{
	register int i;
	register longword ltmp;

	for (i = 1; i <= 8; i++, LARpp_j_1++, LARpp_j++, LARp++) {
		*LARp = GSM_ADD( SASR( *LARpp_j_1, 2 ), SASR( *LARpp_j, 2 ));
		*LARp = GSM_ADD( *LARp, SASR( *LARpp_j, 1 ));
	}
}
