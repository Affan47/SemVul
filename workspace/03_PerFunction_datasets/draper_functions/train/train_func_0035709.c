ide_initialize_drive_parameters (void)
{
	if (ide->hdhfd.size) {
		ide->hdhfd.secspertrack = ide->regs->ide_nsector == 0 ? 256 : ide->regs->ide_nsector;
		ide->hdhfd.heads = (ide->regs->ide_select & 15) + 1;
		ide->hdhfd.cyls = (ide->hdhfd.size / ide->blocksize) / (ide->hdhfd.secspertrack * ide->hdhfd.heads);
		if (ide->hdhfd.heads * ide->hdhfd.cyls * ide->hdhfd.secspertrack > 16515072 || ide->lba48) {
			ide->hdhfd.cyls = ide->hdhfd.cyls_def;
			ide->hdhfd.heads = ide->hdhfd.heads_def;
			ide->hdhfd.secspertrack = ide->hdhfd.secspertrack_def;
		}
	} else {
		ide->regs->ide_error |= IDE_ERR_ABRT;
		ide->status |= IDE_STATUS_ERR;
	}
	write_log (_T("IDE%d initialize drive parameters, CYL=%d,SPT=%d,HEAD=%d\n"),
		ide->num, ide->hdhfd.cyls, ide->hdhfd.secspertrack, ide->hdhfd.heads);
	ide_interrupt ();
}
