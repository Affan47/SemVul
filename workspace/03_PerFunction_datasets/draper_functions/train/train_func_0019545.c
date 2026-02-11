bt878_risc_program(struct bt878 *bt, u32 op_sync_orin)
{
	u32 buf_pos = 0;
	u32 line;

	RISC_FLUSH();
	RISC_INSTR(RISC_SYNC | RISC_SYNC_FM1 | op_sync_orin);
	RISC_INSTR(0);

	dprintk("bt878: risc len lines %u, bytes per line %u\n",
			bt->line_count, bt->line_bytes);
	for (line = 0; line < bt->line_count; line++) {

		if (!(buf_pos % bt->block_bytes))
			RISC_INSTR(RISC_WRITE | RISC_WR_SOL | RISC_WR_EOL |
				   RISC_IRQ |
				   RISC_STATUS(((buf_pos /
						 bt->block_bytes) +
						(bt->block_count -
						 1)) %
					       bt->block_count) | bt->
				   line_bytes);
		else
			RISC_INSTR(RISC_WRITE | RISC_WR_SOL | RISC_WR_EOL |
				   bt->line_bytes);
		RISC_INSTR(bt->buf_dma + buf_pos);
		buf_pos += bt->line_bytes;
	}

	RISC_INSTR(RISC_SYNC | op_sync_orin | RISC_SYNC_VRO);
	RISC_INSTR(0);

	RISC_INSTR(RISC_JUMP);
	RISC_INSTR(bt->risc_dma);

	btwrite((bt->line_count << 16) | bt->line_bytes, BT878_APACK_LEN);
}
