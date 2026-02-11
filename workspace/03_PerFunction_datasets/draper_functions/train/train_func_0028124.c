tun_do_read(struct tun_struct *tun, struct tun_file *tfile,
			   struct iov_iter *to,
			   int noblock)
{
	struct sk_buff *skb;
	ssize_t ret;
	int peeked, err, off = 0;

	tun_debug(KERN_INFO, tun, "tun_do_read\n");

	if (!iov_iter_count(to))
		return 0;


	skb = __skb_recv_datagram(tfile->socket.sk, noblock ? MSG_DONTWAIT : 0,
				  &peeked, &off, &err);
	if (!skb)
		return err;

	ret = tun_put_user(tun, tfile, skb, to);
	if (unlikely(ret < 0))
		kfree_skb(skb);
	else
		consume_skb(skb);

	return ret;
}
