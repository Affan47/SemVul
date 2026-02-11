bnx2x_write_data(struct bnx2x *bp, u32 *buff,
				    u32 addr, u32 len)
{
	int i;
	for (i = 0; i < len; i += 4, buff++)
		REG_WR(bp, addr + i, *buff);
}
