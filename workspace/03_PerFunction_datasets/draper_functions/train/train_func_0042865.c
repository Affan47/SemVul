AcquireForRead()
	{
		XMP_AutoMutex autoMutex ( &this->queueMutex );

		++this->readersWaiting;
		while ( (this->beingWritten) || (this->writersWaiting > 0) ) {

			WaitOnBasicQueue ( this->readerQueue, this->queueMutex );
		}
		--this->readersWaiting;
		XMP_Assert ( ! this->beingWritten );

		++this->lockCount;
	}
