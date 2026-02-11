increment_counter(void)
{
    if(sema_counter[3] == 0x39)
	sema_counter[3] = 0x30;
    else
    {
	sema_counter[3] += 0x01;
	return;
    }
    if(sema_counter[2] == 0x39)
	sema_counter[2] = 0x30;
    else
    {
	sema_counter[2] += 0x01;
	return;
    }
    if(sema_counter[1] == 0x39)
	sema_counter[1] = 0x30;
    else
    {
	sema_counter[1] += 0x01;
	return;
    }
    if(sema_counter[0] == 0x39)
	sema_counter[0] = 0x30;
    else
	sema_counter[0] += 0x01;
    return;
}
