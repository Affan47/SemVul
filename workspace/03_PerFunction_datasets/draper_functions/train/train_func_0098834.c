l1oip_bctrl(struct mISDNchannel *ch, u_int cmd, void *arg)
{
	struct bchannel	*bch = container_of(ch, struct bchannel, ch);
	int		err = -EINVAL;

	if (bch->debug & DEBUG_HW)
		printk(KERN_DEBUG "%s: cmd:%x %p\n",
		       __func__, cmd, arg);
	switch (cmd) {
	case CLOSE_CHANNEL:
		test_and_clear_bit(FLG_OPEN, &bch->Flags);
		test_and_clear_bit(FLG_ACTIVE, &bch->Flags);
		ch->protocol = ISDN_P_NONE;
		ch->peer = NULL;
		module_put(THIS_MODULE);
		err = 0;
		break;
	case CONTROL_CHANNEL:
		err = channel_bctrl(bch, arg);
		break;
	default:
		printk(KERN_WARNING "%s: unknown prim(%x)\n",
		       __func__, cmd);
	}
	return err;
}
