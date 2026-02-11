ppp_mppe_init(void)
{
	int answer;
	if (!(crypto_has_blkcipher("ecb(arc4)", 0, CRYPTO_ALG_ASYNC) &&
	      crypto_has_hash("sha1", 0, CRYPTO_ALG_ASYNC)))
		return -ENODEV;

	sha_pad = kmalloc(sizeof(struct sha_pad), GFP_KERNEL);
	if (!sha_pad)
		return -ENOMEM;
	sha_pad_init(sha_pad);

	answer = ppp_register_compressor(&ppp_mppe);

	if (answer == 0)
		printk(KERN_INFO "PPP MPPE Compression module registered\n");
	else
		kfree(sha_pad);

	return answer;
}
