bnx2x_sample_bulletin(struct bnx2x *bp)
{
	struct pf_vf_bulletin_content *bulletin;
	int attempts;


	for (attempts = 0; attempts < BULLETIN_ATTEMPTS; attempts++) {
		u32 crc;


		memcpy(&bp->shadow_bulletin, bp->pf2vf_bulletin,
		       sizeof(union pf_vf_bulletin));

		crc = bnx2x_crc_vf_bulletin(&bp->shadow_bulletin.content);

		if (bp->shadow_bulletin.content.crc == crc)
			break;

		BNX2X_ERR("bad crc on bulletin board. Contained %x computed %x\n",
			  bp->shadow_bulletin.content.crc, crc);
	}

	if (attempts >= BULLETIN_ATTEMPTS) {
		BNX2X_ERR("pf to vf bulletin board crc was wrong %d consecutive times. Aborting\n",
			  attempts);
		return PFVF_BULLETIN_CRC_ERR;
	}
	bulletin = &bp->shadow_bulletin.content;


	if (bp->old_bulletin.version == bulletin->version)
		return PFVF_BULLETIN_UNCHANGED;


	if (bulletin->valid_bitmap & 1 << MAC_ADDR_VALID &&
	    !ether_addr_equal(bulletin->mac, bp->old_bulletin.mac)) {

		memcpy(bp->dev->dev_addr, bulletin->mac, ETH_ALEN);
	}

	if (bulletin->valid_bitmap & (1 << LINK_VALID)) {
		DP(BNX2X_MSG_IOV, "link update speed %d flags %x\n",
		   bulletin->link_speed, bulletin->link_flags);

		bp->vf_link_vars.line_speed = bulletin->link_speed;
		bp->vf_link_vars.link_report_flags = 0;

		if (bulletin->link_flags & VFPF_LINK_REPORT_LINK_DOWN)
			__set_bit(BNX2X_LINK_REPORT_LINK_DOWN,
				  &bp->vf_link_vars.link_report_flags);

		if (bulletin->link_flags & VFPF_LINK_REPORT_FULL_DUPLEX)
			__set_bit(BNX2X_LINK_REPORT_FD,
				  &bp->vf_link_vars.link_report_flags);

		if (bulletin->link_flags & VFPF_LINK_REPORT_RX_FC_ON)
			__set_bit(BNX2X_LINK_REPORT_RX_FC_ON,
				  &bp->vf_link_vars.link_report_flags);

		if (bulletin->link_flags & VFPF_LINK_REPORT_TX_FC_ON)
			__set_bit(BNX2X_LINK_REPORT_TX_FC_ON,
				  &bp->vf_link_vars.link_report_flags);
		__bnx2x_link_report(bp);
	}


	memcpy(&bp->old_bulletin, bulletin,
	       sizeof(struct pf_vf_bulletin_content));

	return PFVF_BULLETIN_UPDATED;
}
