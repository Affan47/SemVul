wlc_phy_a1_nphy(struct brcms_phy *pi, u8 core, u32 winsz, u32 start,
		u32 end)
{
	u32 *buf, *src, *dst, sz;

	sz = end - start + 1;

	buf = kmalloc(2 * sizeof(u32) * NPHY_PAPD_EPS_TBL_SIZE, GFP_ATOMIC);
	if (NULL == buf)
		return;

	src = buf;
	dst = buf + NPHY_PAPD_EPS_TBL_SIZE;

	wlc_phy_table_read_nphy(pi,
				(core ==
				 PHY_CORE_0 ? NPHY_TBL_ID_EPSILONTBL0 :
				 NPHY_TBL_ID_EPSILONTBL1),
				NPHY_PAPD_EPS_TBL_SIZE, 0, 32, src);

	do {
		u32 phy_a1, phy_a2;
		s32 phy_a3, phy_a4, phy_a5, phy_a6, phy_a7;

		phy_a1 = end - min(end, (winsz >> 1));
		phy_a2 = min_t(u32, NPHY_PAPD_EPS_TBL_SIZE - 1,
			       end + (winsz >> 1));
		phy_a3 = phy_a2 - phy_a1 + 1;
		phy_a6 = 0;
		phy_a7 = 0;

		do {
			wlc_phy_papd_decode_epsilon(src[phy_a2], &phy_a4,
						    &phy_a5);
			phy_a6 += phy_a4;
			phy_a7 += phy_a5;
		} while (phy_a2-- != phy_a1);

		phy_a6 /= phy_a3;
		phy_a7 /= phy_a3;
		dst[end] = ((u32) phy_a7 << 13) | ((u32) phy_a6 & 0x1fff);
	} while (end-- != start);

	wlc_phy_table_write_nphy(pi,
				 (core ==
				  PHY_CORE_0) ? NPHY_TBL_ID_EPSILONTBL0 :
				 NPHY_TBL_ID_EPSILONTBL1, sz, start, 32, dst);

	kfree(buf);
}
