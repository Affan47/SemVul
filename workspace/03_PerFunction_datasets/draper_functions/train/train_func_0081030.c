bfa_uf_post(struct bfa_uf_mod_s *ufm, struct bfa_uf_s *uf)
{
	struct bfi_uf_buf_post_s *uf_post_msg;

	uf_post_msg = bfa_reqq_next(ufm->bfa, BFA_REQQ_FCXP);
	if (!uf_post_msg)
		return BFA_STATUS_FAILED;

	memcpy(uf_post_msg, &ufm->uf_buf_posts[uf->uf_tag],
		      sizeof(struct bfi_uf_buf_post_s));
	bfa_reqq_produce(ufm->bfa, BFA_REQQ_FCXP, uf_post_msg->mh);

	bfa_trc(ufm->bfa, uf->uf_tag);

	list_add_tail(&uf->qe, &ufm->uf_posted_q);
	return BFA_STATUS_OK;
}
