FIFO_data_write(int data)
{

	if (fifo_count < FIFO_SIZE)
	{
		fifo[fifo_tail] = (data&1);

		fifo_tail = (fifo_tail + 1) % FIFO_SIZE;
		fifo_count++;

		if (DEBUG_5110) logerror("Added bit to FIFO (size=%2d)\n", fifo_count);
	}
	else
	{
		if (DEBUG_5110) logerror("Ran out of room in the FIFO!\n");
	}
}
