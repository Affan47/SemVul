esas2r_build_ae_req(struct esas2r_adapter *a, struct esas2r_request *rq)
{
	struct atto_vda_ae_req *vrq = &rq->vrq->ae;

	clear_vda_request(rq);

	rq->vrq->scsi.function = VDA_FUNC_AE;

	vrq->length = cpu_to_le32(sizeof(struct atto_vda_ae_data));

	if (test_bit(AF_LEGACY_SGE_MODE, &a->flags)) {
		vrq->sg_list_offset =
			(u8)offsetof(struct atto_vda_ae_req, sge);
		vrq->sge[0].length = cpu_to_le32(SGE_LAST | vrq->length);
		vrq->sge[0].address = cpu_to_le64(
			rq->vrq_md->phys_addr +
			sizeof(union atto_vda_req));
	} else {
		vrq->sg_list_offset = (u8)offsetof(struct atto_vda_ae_req,
						   prde);
		vrq->prde[0].ctl_len = cpu_to_le32(vrq->length);
		vrq->prde[0].address = cpu_to_le64(
			rq->vrq_md->phys_addr +
			sizeof(union atto_vda_req));
	}
}
