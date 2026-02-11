stopParserThread()
{
	if ( _parserThread.get() )
	{
		requestParserThreadKill();
		_parserThread->join();
		_parserThread.reset();
	}
}
