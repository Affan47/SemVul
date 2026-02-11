src1_3src (FILE *file, struct brw_instruction *inst)
{
    int err = 0;
    unsigned swz_x = (inst->bits2.da3src.src1_swizzle >> 0) & 0x3;
    unsigned swz_y = (inst->bits2.da3src.src1_swizzle >> 2) & 0x3;
    unsigned swz_z = (inst->bits2.da3src.src1_swizzle >> 4) & 0x3;
    unsigned swz_w = (inst->bits2.da3src.src1_swizzle >> 6) & 0x3;
    unsigned src1_subreg_nr = (inst->bits2.da3src.src1_subreg_nr_low |
			     (inst->bits3.da3src.src1_subreg_nr_high << 2));

    err |= control (file, "negate", negate, inst->bits1.da3src.src1_negate,
		    NULL);
    err |= control (file, "abs", _abs, inst->bits1.da3src.src1_abs, NULL);

    err |= reg (file, BRW_GENERAL_REGISTER_FILE,
		inst->bits3.da3src.src1_reg_nr);
    if (err == -1)
	return 0;
    if (src1_subreg_nr)
	format (file, ".%d", src1_subreg_nr);
    string (file, "<4,1,1>");
    err |= control (file, "src da16 reg type", three_source_reg_encoding,
                    inst->bits1.da3src.src_type, NULL);


    if (swz_x == BRW_CHANNEL_X &&
	swz_y == BRW_CHANNEL_Y &&
	swz_z == BRW_CHANNEL_Z &&
	swz_w == BRW_CHANNEL_W)
    {
	;
    }
    else if (swz_x == swz_y && swz_x == swz_z && swz_x == swz_w)
    {
	string (file, ".");
	err |= control (file, "channel select", chan_sel, swz_x, NULL);
    }
    else
    {
	string (file, ".");
	err |= control (file, "channel select", chan_sel, swz_x, NULL);
	err |= control (file, "channel select", chan_sel, swz_y, NULL);
	err |= control (file, "channel select", chan_sel, swz_z, NULL);
	err |= control (file, "channel select", chan_sel, swz_w, NULL);
    }
    return err;
}
