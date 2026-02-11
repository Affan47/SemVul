ccdbg_get_pc(struct ccdbg *dbg)
{
	uint16_t	pc1, pc2;

	pc1 = ccdbg_cmd_write_read16(dbg, CC_GET_PC, NULL, 0);
	pc2 = ccdbg_cmd_write_read16(dbg, CC_GET_PC, NULL, 0);
	if (pc1 != pc2)
		fprintf (stderr, "Invalid pc %04x != %04x\n",
			 pc1, pc2);
	return pc2;
}
