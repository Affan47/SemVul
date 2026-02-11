mega_mod64(u64 dividend, u32 divisor)
{
	u64 d;
	u32 remainder;

	if (!divisor)
		printk(KERN_ERR "megasas : DIVISOR is zero, in div fn\n");
	d = dividend;
	remainder = do_div(d, divisor);
	return remainder;
}
