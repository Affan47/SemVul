iblock_bio_done(struct bio *bio)
{
	struct se_cmd *cmd = bio->bi_private;
	struct iblock_req *ibr = cmd->priv;

	if (bio->bi_error) {
		pr_err("bio error: %p,  err: %d\n", bio, bio->bi_error);


		atomic_inc(&ibr->ib_bio_err_cnt);
		smp_mb__after_atomic();
	}

	bio_put(bio);

	iblock_complete_cmd(cmd);
}
