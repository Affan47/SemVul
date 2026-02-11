StrategyRejectBuffer(BufferAccessStrategy strategy, volatile BufferDesc *buf)
{

	if (strategy->btype != BAS_BULKREAD)
		return false;


	if (!strategy->current_was_in_ring ||
	  strategy->buffers[strategy->current] != BufferDescriptorGetBuffer(buf))
		return false;


	strategy->buffers[strategy->current] = InvalidBuffer;

	return true;
}
