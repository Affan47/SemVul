send_break()
{
    unsigned char buf[1600];
    unsigned char slotbuf[10];
    int  ptr = 0;
    int command = 0xA0;

    if (remote_credit <= 1)
    {
	debuglog(("Sending more remote credit with break\n"));
	remote_credit += 5;
	command |= 0x5;
    }

    slotbuf[0] = 0x10;
    add_slot(buf, ptr, command, slotbuf, 1);

    parent.queue_message(buf, ptr);
    return 0;
}
