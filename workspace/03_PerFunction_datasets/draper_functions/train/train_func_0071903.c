bfa_tskim_alloc(struct bfa_s *bfa, struct bfad_tskim_s *dtsk)
{
	struct bfa_fcpim_s *fcpim = BFA_FCPIM(bfa);
	struct bfa_tskim_s *tskim;

	bfa_q_deq(&fcpim->tskim_free_q, &tskim);

	if (tskim)
		tskim->dtsk = dtsk;

	return tskim;
}
