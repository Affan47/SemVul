tg3_mdio_read(struct mii_bus *bp, int mii_id, int reg)
{
	struct tg3 *tp = bp->priv;
	u32 val;

	spin_lock_bh(&tp->lock);

	if (__tg3_readphy(tp, mii_id, reg, &val))
		val = -EIO;

	spin_unlock_bh(&tp->lock);

	return val;
}
