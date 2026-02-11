get_board_id(void *vsd, char *board_id)
{
	int i;

#define VSD_OFFSET_SIG1		0x00
#define VSD_OFFSET_SIG2		0xde
#define VSD_OFFSET_MLX_BOARD_ID	0xd0
#define VSD_OFFSET_TS_BOARD_ID	0x20

#define VSD_SIGNATURE_TOPSPIN	0x5ad

	memset(board_id, 0, MLX4_BOARD_ID_LEN);

	if (be16_to_cpup(vsd + VSD_OFFSET_SIG1) == VSD_SIGNATURE_TOPSPIN &&
	    be16_to_cpup(vsd + VSD_OFFSET_SIG2) == VSD_SIGNATURE_TOPSPIN) {
		strlcpy(board_id, vsd + VSD_OFFSET_TS_BOARD_ID, MLX4_BOARD_ID_LEN);
	} else {


		u32 *bid_u32 = (u32 *)board_id;

		for (i = 0; i < 4; ++i) {
			u32 *addr;
			u32 val;

			addr = (u32 *) (vsd + VSD_OFFSET_MLX_BOARD_ID + i * 4);
			val = get_unaligned(addr);
			val = swab32(val);
			put_unaligned(val, &bid_u32[i]);
		}
	}
}
