dump_edp(int length)
{
	struct bdb_block *block;
	struct bdb_edp *edp;
	int bpp;

	block = find_section(BDB_EDP, length);
	if (!block) {
		printf("No EDP data block\n");
		return;
	}
	edp = block->data;

	printf("eDP block: type %d\n", panel_type);
	printf("\tPower Sequence: T3 %d T7 %d T9 %d T10 %d T12 %d\n",
		edp->power_seqs[panel_type].t3,
		edp->power_seqs[panel_type].t7,
		edp->power_seqs[panel_type].t9,
		edp->power_seqs[panel_type].t10,
		edp->power_seqs[panel_type].t12);

	bpp = (edp->color_depth >> (panel_type * 2)) & 3;

	printf("\tPanel color depth: ");
	switch (bpp) {
	case EDP_18BPP:
		printf("18bpp\n");
		break;
	case EDP_24BPP:
		printf("24bpp\n");
		break;
	case EDP_30BPP:
		printf("30bpp\n");
		break;
	}
	printf("\teDP sDRRs MSA timing delay: %d\n", edp->sdrrs_msa_timing_delay);
	printf("\tLink params:\n");
	printf("\t\trate: ");
	if (edp->link_params[panel_type].rate == EDP_RATE_1_62)
		printf("1.62G\n");
	else if (edp->link_params[panel_type].rate == EDP_RATE_2_7)
		printf("2.7G\n");
	printf("\t\tlanes: ");
	switch (edp->link_params[panel_type].lanes) {
	case EDP_LANE_1:
		printf("x1 mode\n");
		break;
	case EDP_LANE_2:
		printf("x2 mode\n");
		break;
	case EDP_LANE_4:
		printf("x4 mode\n");
		break;
	}
	printf("\t\tpre-emphasis: ");
	switch (edp->link_params[panel_type].preemphasis) {
	case EDP_PREEMPHASIS_NONE:
		printf("none\n");
		break;
	case EDP_PREEMPHASIS_3_5dB:
		printf("3.5dB\n");
		break;
	case EDP_PREEMPHASIS_6dB:
		printf("6dB\n");
		break;
	case EDP_PREEMPHASIS_9_5dB:
		printf("9.5dB\n");
		break;
	}
	printf("\t\tvswing: ");
	switch (edp->link_params[panel_type].vswing) {
	case EDP_VSWING_0_4V:
		printf("0.4V\n");
		break;
	case EDP_VSWING_0_6V:
		printf("0.6V\n");
		break;
	case EDP_VSWING_0_8V:
		printf("0.8V\n");
		break;
	case EDP_VSWING_1_2V:
		printf("1.2V\n");
		break;
	}
	free(block);
}
