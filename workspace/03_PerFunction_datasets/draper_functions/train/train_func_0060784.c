ndmp_9to3_mover_connect_request (
  ndmp9_mover_connect_request *request9,
  ndmp3_mover_connect_request *request3)
{
	int		rc;

	rc = CNVT_E_FROM_9 (request3, request9, mode, ndmp_39_mover_mode);
	if (rc == NDMP_INVALID_GENERAL) {
		 CNVT_FROM_9 (request3, request9, mode);
	}
	return ndmp_9to3_addr (&request9->addr, &request3->addr);
}
