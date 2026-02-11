ide_execute_drive_diagnostics (bool irq)
{
	ide->regs->ide_error = 1;
	ide->regs->ide_sector = ide->regs->ide_nsector = 1;
	ide->regs->ide_select = 0;
	ide->regs->ide_lcyl = ide->regs->ide_hcyl = 0;
	if (irq)
		ide_interrupt ();
	else
		ide->status = ~IDE_STATUS_BSY;
}
