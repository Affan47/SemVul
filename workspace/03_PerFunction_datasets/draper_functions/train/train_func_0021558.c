peek() const
{
	mutex_lock_guard l(messages->mutex);
	return locked_peek();
}
