init (uint32_t size)
{
        thread_buffers = new ThreadBufferFIFO (size+1);
	thread_buffers_list = new ThreadBufferList;


        for (uint32_t n = 0; n < size; ++n) {
                ThreadBuffers* ts = new ThreadBuffers;
                thread_buffers->write (&ts, 1);
		thread_buffers_list->push_back (ts);
        }


}
