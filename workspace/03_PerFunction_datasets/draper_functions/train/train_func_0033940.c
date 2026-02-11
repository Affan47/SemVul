bfa_fru_intr(void *fruarg, struct bfi_mbmsg_s *msg)
{
	struct bfa_fru_s *fru = fruarg;
	struct bfi_fru_rsp_s *rsp = (struct bfi_fru_rsp_s *)msg;
	u32 status;

	bfa_trc(fru, msg->mh.msg_id);

	if (!fru->op_busy) {


		bfa_trc(fru, 0x9999);
		return;
	}

	switch (msg->mh.msg_id) {
	case BFI_FRUVPD_I2H_WRITE_RSP:
	case BFI_TFRU_I2H_WRITE_RSP:
		status = be32_to_cpu(rsp->status);
		bfa_trc(fru, status);

		if (status != BFA_STATUS_OK || fru->residue == 0) {
			fru->status = status;
			fru->op_busy = 0;
			if (fru->cbfn)
				fru->cbfn(fru->cbarg, fru->status);
		} else {
			bfa_trc(fru, fru->offset);
			if (msg->mh.msg_id == BFI_FRUVPD_I2H_WRITE_RSP)
				bfa_fru_write_send(fru,
					BFI_FRUVPD_H2I_WRITE_REQ);
			else
				bfa_fru_write_send(fru,
					BFI_TFRU_H2I_WRITE_REQ);
		}
		break;
	case BFI_FRUVPD_I2H_READ_RSP:
	case BFI_TFRU_I2H_READ_RSP:
		status = be32_to_cpu(rsp->status);
		bfa_trc(fru, status);

		if (status != BFA_STATUS_OK) {
			fru->status = status;
			fru->op_busy = 0;
			if (fru->cbfn)
				fru->cbfn(fru->cbarg, fru->status);
		} else {
			u32 len = be32_to_cpu(rsp->length);

			bfa_trc(fru, fru->offset);
			bfa_trc(fru, len);

			memcpy(fru->ubuf + fru->offset, fru->dbuf_kva, len);
			fru->residue -= len;
			fru->offset += len;

			if (fru->residue == 0) {
				fru->status = status;
				fru->op_busy = 0;
				if (fru->cbfn)
					fru->cbfn(fru->cbarg, fru->status);
			} else {
				if (msg->mh.msg_id == BFI_FRUVPD_I2H_READ_RSP)
					bfa_fru_read_send(fru,
						BFI_FRUVPD_H2I_READ_REQ);
				else
					bfa_fru_read_send(fru,
						BFI_TFRU_H2I_READ_REQ);
			}
		}
		break;
	default:
		WARN_ON(1);
	}
}
