phantom_destroy_rx_ctx ( struct phantom_nic *phantom ) {
	int rc;

	DBGC ( phantom, "Phantom %p destroying RX context (id %04x)\n",
	       phantom, phantom->rx_context_id );


	if ( ( rc = phantom_issue_cmd ( phantom,
					NX_CDRP_CMD_DESTROY_RX_CTX,
					phantom->rx_context_id,
					NX_DESTROY_CTX_RESET, 0 ) ) != 0 ) {
		DBGC ( phantom, "Phantom %p could not destroy RX context: "
		       "%s\n", phantom, strerror ( rc ) );

		return;
	}


	phantom->rx_context_id = 0;
	phantom->rds_producer_crb = 0;
	phantom->sds_consumer_crb = 0;


	phantom->rds_producer_idx = 0;
	phantom->rds_consumer_idx = 0;
	phantom->sds_consumer_idx = 0;
}
