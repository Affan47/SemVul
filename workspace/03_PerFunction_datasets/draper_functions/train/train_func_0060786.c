i_usX2Y_Out04Int(struct urb *urb)
{
#ifdef CONFIG_SND_DEBUG
	if (urb->status) {
		int 		i;
		struct usX2Ydev *usX2Y = urb->context;
		for (i = 0; i < 10 && usX2Y->AS04.urb[i] != urb; i++);
		snd_printdd("i_usX2Y_Out04Int() urb %i status=%i\n", i, urb->status);
	}
#endif
}
