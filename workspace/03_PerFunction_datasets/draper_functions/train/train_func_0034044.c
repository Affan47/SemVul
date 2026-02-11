mlx4_en_bounce_to_desc(struct mlx4_en_priv *priv,
						      struct mlx4_en_tx_ring *ring,
						      u32 index,
						      unsigned int desc_size)
{
	u32 copy = (ring->size - index) * TXBB_SIZE;
	int i;

	for (i = desc_size - copy - 4; i >= 0; i -= 4) {
		if ((i & (TXBB_SIZE - 1)) == 0)
			wmb();

		*((u32 *) (ring->buf + i)) =
			*((u32 *) (ring->bounce_buf + copy + i));
	}

	for (i = copy - 4; i >= 4 ; i -= 4) {
		if ((i & (TXBB_SIZE - 1)) == 0)
			wmb();

		*((u32 *) (ring->buf + index * TXBB_SIZE + i)) =
			*((u32 *) (ring->bounce_buf + i));
	}


	return ring->buf + index * TXBB_SIZE;
}
