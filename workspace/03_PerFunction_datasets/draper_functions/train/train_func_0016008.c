ide_exec_command(ide_hwif_t *hwif, u8 cmd)
{
	if (hwif->host_flags & IDE_HFLAG_MMIO)
		writeb(cmd, (void __iomem *)hwif->io_ports.command_addr);
	else
		outb(cmd, hwif->io_ports.command_addr);
}
