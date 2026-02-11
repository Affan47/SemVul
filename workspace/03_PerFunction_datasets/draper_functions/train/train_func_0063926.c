PushSequenceAddr( struct sequence *pSequence, int addr )
{
	if( pSequence->stackSize<MAX_SEQUENCE_RECURSION )
	{
		pSequence->stackData[pSequence->stackSize++] = addr;
	}
	else
	{
		logerror( "sound/namcona.c stack overflow!\n" );
	}
}
