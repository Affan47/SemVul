ath9k_multi_ioread32(void *hw_priv, u32 *addr,
                                u32 *val, u16 count)
{
	int i;

	for (i = 0; i < count; i++)
		val[i] = ath9k_ioread32(hw_priv, addr[i]);
}
