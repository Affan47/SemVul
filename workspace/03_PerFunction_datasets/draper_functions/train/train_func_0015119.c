esas2r_handle_outbound_rsp_err(struct esas2r_adapter *a,
					   struct esas2r_request *rq,
					   struct atto_vda_ob_rsp *rsp)
{


	if (unlikely(rq->req_stat != RS_SUCCESS)) {
		memcpy(&rq->func_rsp, &rsp->func_rsp, sizeof(rsp->func_rsp));

		if (rq->req_stat == RS_ABORTED) {
			if (rq->timeout > RQ_MAX_TIMEOUT)
				rq->req_stat = RS_TIMEOUT;
		} else if (rq->req_stat == RS_SCSI_ERROR) {
			u8 scsistatus = rq->func_rsp.scsi_rsp.scsi_stat;

			esas2r_trace("scsistatus: %x", scsistatus);


			if (scsistatus == SAM_STAT_GOOD || scsistatus ==
			    SAM_STAT_CONDITION_MET || scsistatus ==
			    SAM_STAT_INTERMEDIATE || scsistatus ==
			    SAM_STAT_INTERMEDIATE_CONDITION_MET) {
				rq->req_stat = RS_SUCCESS;
				rq->func_rsp.scsi_rsp.scsi_stat =
					SAM_STAT_GOOD;
			}
		}
	}
}
