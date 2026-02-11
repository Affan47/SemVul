uaeserialdev_startup (uaecptr resaddr)
{
	if (!currprefs.uaeserial)
		return resaddr;
	if (log_uaeserial)
		write_log (_T("uaeserialdev_startup(0x%x)\n"), resaddr);


	put_word (resaddr + 0x0, 0x4AFC);
	put_long (resaddr + 0x2, resaddr);
	put_long (resaddr + 0x6, resaddr + 0x1A);
	put_word (resaddr + 0xA, 0x8101);
	put_word (resaddr + 0xC, 0x0305);
	put_long (resaddr + 0xE, ROM_uaeserialdev_resname);
	put_long (resaddr + 0x12, ROM_uaeserialdev_resid);
	put_long (resaddr + 0x16, ROM_uaeserialdev_init);
	resaddr += 0x1A;
	return resaddr;
}
