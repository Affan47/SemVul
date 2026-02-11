iscsi_conn_queue_work(struct iscsi_conn *conn)
{
	struct Scsi_Host *shost = conn->session->host;
	struct iscsi_host *ihost = shost_priv(shost);

	if (ihost->workq)
		queue_work(ihost->workq, &conn->xmitwork);
}
