vmw_fifo_slow_copy(struct vmw_fifo_state *fifo_state,
			       u32  *fifo_mem,
			       uint32_t next_cmd,
			       uint32_t max, uint32_t min, uint32_t bytes)
{
	uint32_t *buffer = (fifo_state->dynamic_buffer != NULL) ?
	    fifo_state->dynamic_buffer : fifo_state->static_buffer;

	while (bytes > 0) {
		vmw_mmio_write(*buffer++, fifo_mem + (next_cmd >> 2));
		next_cmd += sizeof(uint32_t);
		if (unlikely(next_cmd == max))
			next_cmd = min;
		mb();
		vmw_mmio_write(next_cmd, fifo_mem + SVGA_FIFO_NEXT_CMD);
		mb();
		bytes -= sizeof(uint32_t);
	}
}
