ppa_completion(struct scsi_cmnd *cmd)
{


	ppa_struct *dev = ppa_dev(cmd->device->host);
	unsigned short ppb = dev->base;
	unsigned long start_jiffies = jiffies;

	unsigned char r, v;
	int fast, bulk, status;

	v = cmd->cmnd[0];
	bulk = ((v == READ_6) ||
		(v == READ_10) || (v == WRITE_6) || (v == WRITE_10));


	r = (r_str(ppb) & 0xf0);

	while (r != (unsigned char) 0xf0) {


		if (time_after(jiffies, start_jiffies + 1))
			return 0;

		if ((cmd->SCp.this_residual <= 0)) {
			ppa_fail(dev, DID_ERROR);
			return -1;
		}


		if ((r & 0xc0) != 0xc0) {


			unsigned long k = dev->recon_tmo;
			for (; k && ((r = (r_str(ppb) & 0xf0)) & 0xc0) != 0xc0;
			     k--)
				udelay(1);

			if (!k)
				return 0;
		}


		fast = (bulk && (cmd->SCp.this_residual >= PPA_BURST_SIZE))
		    ? PPA_BURST_SIZE : 1;

		if (r == (unsigned char) 0xc0)
			status = ppa_out(dev, cmd->SCp.ptr, fast);
		else
			status = ppa_in(dev, cmd->SCp.ptr, fast);

		cmd->SCp.ptr += fast;
		cmd->SCp.this_residual -= fast;

		if (!status) {
			ppa_fail(dev, DID_BUS_BUSY);
			return -1;
		}
		if (cmd->SCp.buffer && !cmd->SCp.this_residual) {

			if (cmd->SCp.buffers_residual--) {
				cmd->SCp.buffer++;
				cmd->SCp.this_residual =
				    cmd->SCp.buffer->length;
				cmd->SCp.ptr = sg_virt(cmd->SCp.buffer);
			}
		}

		r = (r_str(ppb) & 0xf0);

		if (!(r & 0x80))
			return 0;
	}
	return 1;
}
