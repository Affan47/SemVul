signal_delayed_interrupt(struct ide_state *ide, double time, int buffer_ready)
{

	ide->status &= ~IDE_STATUS_BUFFER_READY;
	ide->status |= IDE_STATUS_BUSY;


	if (buffer_ready)
		timer_set(time, ide - idestate, delayed_interrupt_buffer_ready);
	else
		timer_set(time, ide - idestate, delayed_interrupt);
}
