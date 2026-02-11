continue_write(struct ide_state *ide)
{

	ide->buffer_offset = 0;


	ide->status &= ~IDE_STATUS_BUFFER_READY;
	ide->status |= IDE_STATUS_BUSY;

	if (ide->command == IDE_COMMAND_WRITE_MULTIPLE_BLOCK)
	{
		if (ide->sectors_until_int != 1)
		{

			write_sector_done(ide - idestate);
		}
		else
		{

			timer_set(TIME_PER_SECTOR, ide - idestate, write_sector_done);
		}
	}
	else
	{

		timer_set(TIME_PER_SECTOR, ide - idestate, write_sector_done);
	}
}
