mtnic_HEART_BEAT(struct mtnic_port *priv, u32 *link_state)
{
	struct mtnic_if_heart_beat_out_imm heart_beat;

	int err;
	u32 flags;
	err = mtnic_cmd(priv->mtnic, NULL, &heart_beat, 0, MTNIC_IF_CMD_HEART_BEAT);
	if (!err) {
		flags = be32_to_cpu(heart_beat.flags);
		if (flags & MTNIC_BC_MASK(MTNIC_MASK_HEAR_BEAT_INT_ERROR)) {
			DBG("Internal error detected\n");
			return -EIO;
		}
		*link_state = flags &
			      ~((u32) MTNIC_BC_MASK(MTNIC_MASK_HEAR_BEAT_INT_ERROR));
	}
	return err;
}
