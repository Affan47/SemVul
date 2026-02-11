rsc_mgr_init(struct rsc_mgr *mgr, enum RSCTYP type,
		 unsigned int amount, struct hw *hw)
{
	int err = 0;

	mgr->type = NUM_RSCTYP;

	mgr->rscs = kzalloc(((amount + 8 - 1) / 8), GFP_KERNEL);
	if (!mgr->rscs)
		return -ENOMEM;

	switch (type) {
	case SRC:
		err = hw->src_mgr_get_ctrl_blk(&mgr->ctrl_blk);
		break;
	case SRCIMP:
		err = hw->srcimp_mgr_get_ctrl_blk(&mgr->ctrl_blk);
		break;
	case AMIXER:
		err = hw->amixer_mgr_get_ctrl_blk(&mgr->ctrl_blk);
		break;
	case DAIO:
		err = hw->daio_mgr_get_ctrl_blk(hw, &mgr->ctrl_blk);
		break;
	case SUM:
		break;
	default:
		dev_err(hw->card->dev,
			"Invalid resource type value %d!\n", type);
		err = -EINVAL;
		goto error;
	}

	if (err) {
		dev_err(hw->card->dev,
			"Failed to get manager control block!\n");
		goto error;
	}

	mgr->type = type;
	mgr->avail = mgr->amount = amount;
	mgr->hw = hw;

	return 0;

error:
	kfree(mgr->rscs);
	return err;
}
