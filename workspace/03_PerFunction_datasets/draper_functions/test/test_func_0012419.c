__mmc_start_data_req(struct mmc_host *host, struct mmc_request *mrq)
{
	int err;

	mrq->done = mmc_wait_data_done;
	mrq->host = host;

	err = mmc_start_request(host, mrq);
	if (err) {
		mrq->cmd->error = err;
		mmc_wait_data_done(mrq);
	}

	return err;
}
