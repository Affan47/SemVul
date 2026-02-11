ClearUsbDevice()
{
	scoped_lock lock(m_mutex);
	m_dev = 0;
	m_usb_error_dev_callback.reset();
	lock.unlock();


	scoped_lock wait(m_readwaitMutex);
	pthread_cond_wait(&m_readwaitCond, &m_readwaitMutex);
}
