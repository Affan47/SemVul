AccumCleanup ( void * pArg )
{
	RtAccum_t * pAcc = (RtAccum_t *) pArg;
	SafeDelete ( pAcc );
}
