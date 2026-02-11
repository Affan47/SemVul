natsemi_irq (struct net_device *netdev, int enable)
{
        struct natsemi_private *np = netdev->priv;

	outl ((enable ? (RxOk | RxErr | TxOk|TxErr) : 0),
	      np->ioaddr + IntrMask);
	outl ((enable ? 1 : 0), np->ioaddr + IntrEnable);
}
