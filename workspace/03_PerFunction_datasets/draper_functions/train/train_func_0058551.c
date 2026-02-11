continue_read(struct ide_state *ide)
{

	ide->buffer_offset = 0;


	ide->status &= ~IDE_STATUS_BUFFER_READY;

	if (ide->master_password_enable || ide->user_password_enable)
	{
		security_error(ide);

		ide->sector_count = 0;
		ide->bus_master_status &= ~IDE_BUSMASTER_STATUS_ACTIVE;
		ide->dma_active = 0;

		return;
	}


	if (ide->sector_count > 0)
		ide->sector_count--;
	if (ide->sector_count > 0)
		read_next_sector(ide);
	else
	{
		ide->bus_master_status &= ~IDE_BUSMASTER_STATUS_ACTIVE;
		ide->dma_active = 0;
	}
}
