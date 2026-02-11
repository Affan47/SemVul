ch_set_voltag(scsi_changer *ch, u_int elem,
	      int alternate, int clear, u_char *tag)
{
	u_char  cmd[12];
	u_char  *buffer;
	int result;

	buffer = kzalloc(512, GFP_KERNEL);
	if (!buffer)
		return -ENOMEM;

	DPRINTK("%s %s voltag: 0x%x => \"%s\"\n",
		clear     ? "clear"     : "set",
		alternate ? "alternate" : "primary",
		elem, tag);
	memset(cmd,0,sizeof(cmd));
	cmd[0]  = SEND_VOLUME_TAG;
	cmd[1] = ((ch->device->lun & 0x7) << 5) |
		ch_elem_to_typecode(ch,elem);
	cmd[2] = (elem >> 8) & 0xff;
	cmd[3] = elem        & 0xff;
	cmd[5] = clear
		? (alternate ? 0x0d : 0x0c)
		: (alternate ? 0x0b : 0x0a);

	cmd[9] = 255;

	memcpy(buffer,tag,32);
	ch_check_voltag(buffer);

	result = ch_do_scsi(ch, cmd, 12, buffer, 256, DMA_TO_DEVICE);
	kfree(buffer);
	return result;
}
