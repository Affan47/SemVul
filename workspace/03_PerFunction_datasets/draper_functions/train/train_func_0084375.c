PopControl(unsigned id)
{
	Mutex::ScopedLock lock( mDataMutex );
#ifdef HAVE_STANDARD_VECTOR_AT
	TControlData ret=mDataQueues.at(id).front();
#else
	TControlData ret=mDataQueues[id].front();
#endif
	mDataQueues[id].pop();
	return ret;
}
