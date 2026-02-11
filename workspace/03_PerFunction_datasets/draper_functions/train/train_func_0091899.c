cfi_udelay(int us)
{
	if (us >= 1000) {
		msleep((us+999)/1000);
	} else {
		udelay(us);
		cond_resched();
	}
}
