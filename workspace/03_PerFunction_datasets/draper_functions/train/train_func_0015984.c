smsc_check(int io, int key)
{
	int origval, id, rev, oldid, oldrev, x_id, x_rev, x_oldid, x_oldrev;

	if (!request_region(io, 3, __func__))
		return;

	origval = inb(io);


	outb(0x0d, io);
	x_oldid = inb(io + 1);
	outb(0x0e, io);
	x_oldrev = inb(io + 1);
	outb(0x20, io);
	x_id = inb(io + 1);
	outb(0x21, io);
	x_rev = inb(io + 1);

	outb(key, io);
	outb(key, io);

	outb(0x0d, io);
	oldid = inb(io + 1);
	outb(0x0e, io);
	oldrev = inb(io + 1);
	outb(0x20, io);
	id = inb(io + 1);
	outb(0x21, io);
	rev = inb(io + 1);
	outb(0xaa, io);

	outb(origval, io);

	if (x_id == id && x_oldrev == oldrev &&
	    x_oldid == oldid && x_rev == rev)
		goto out;

	decode_smsc(io, key, oldid, oldrev);
out:
	release_region(io, 3);
}
