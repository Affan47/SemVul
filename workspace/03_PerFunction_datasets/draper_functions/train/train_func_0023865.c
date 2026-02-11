bfa_ioc_mbox_queue(struct bfa_ioc_s *ioc, struct bfa_mbox_cmd_s *cmd)
{
	struct bfa_ioc_mbox_mod_s	*mod = &ioc->mbox_mod;
	u32			stat;


	if (!list_empty(&mod->cmd_q)) {
		list_add_tail(&cmd->qe, &mod->cmd_q);
		return;
	}


	stat = readl(ioc->ioc_regs.hfn_mbox_cmd);
	if (stat) {
		list_add_tail(&cmd->qe, &mod->cmd_q);
		return;
	}


	bfa_ioc_mbox_send(ioc, cmd->msg, sizeof(cmd->msg));
}
