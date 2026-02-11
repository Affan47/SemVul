ipmi_set_my_LUN(ipmi_user_t   user,
		    unsigned int  channel,
		    unsigned char LUN)
{
	if (channel >= IPMI_MAX_CHANNELS)
		return -EINVAL;
	user->intf->channels[channel].lun = LUN & 0x3;
	return 0;
}
