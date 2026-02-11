onTimer( int, short, void * arg )
{
	SP_PushArg_t * pushArg = (SP_PushArg_t*)arg;

	pushArg->mEventArg->getInputResultQueue()->push(
		new SP_SimpleTask( timer, pushArg, 1 ) );
}
