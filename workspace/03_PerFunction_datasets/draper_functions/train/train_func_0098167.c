csio_rns_offline(struct csio_rnode *rn, enum csio_rn_ev evt)
{
	struct csio_lnode *ln = csio_rnode_to_lnode(rn);
	int ret = 0;

	CSIO_INC_STATS(rn, n_evt_sm[evt]);

	switch (evt) {
	case CSIO_RNFE_LOGGED_IN:
	case CSIO_RNFE_PLOGI_RECV:
		ret = csio_rn_verify_rparams(ln, rn, rn->rdev_entry);
		if (!ret) {
			csio_set_state(&rn->sm, csio_rns_ready);
			__csio_reg_rnode(rn);
		} else {
			CSIO_INC_STATS(rn, n_err_inval);
			csio_post_event(&rn->sm, CSIO_RNFE_CLOSE);
		}
		break;

	case CSIO_RNFE_DOWN:
		csio_ln_dbg(ln,
			"ssni:x%x Ignoring event %d recv from did:x%x "
			"in rn state[offline]\n", csio_rn_flowid(rn), evt,
			rn->nport_id);
		CSIO_INC_STATS(rn, n_evt_drop);
		break;

	case CSIO_RNFE_CLOSE:


		csio_set_state(&rn->sm, csio_rns_uninit);
		break;

	case CSIO_RNFE_NAME_MISSING:
		csio_set_state(&rn->sm, csio_rns_disappeared);
		break;

	default:
		csio_ln_dbg(ln,
			"ssni:x%x unexp event %d recv from did:x%x "
			"in rn state[offline]\n", csio_rn_flowid(rn), evt,
			rn->nport_id);
		CSIO_INC_STATS(rn, n_evt_unexp);
		break;
	}
}
