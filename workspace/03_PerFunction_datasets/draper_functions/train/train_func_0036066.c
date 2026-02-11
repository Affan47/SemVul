creg_issue_cmd(struct rsxx_cardinfo *card, struct creg_cmd *cmd)
{
	int st;

	if (unlikely(card->eeh_state))
		return;

	iowrite32(cmd->addr, card->regmap + CREG_ADD);
	iowrite32(cmd->cnt8, card->regmap + CREG_CNT);

	if (cmd->op == CREG_OP_WRITE) {
		if (cmd->buf) {
			st = copy_to_creg_data(card, cmd->cnt8,
					       cmd->buf, cmd->stream);
			if (st)
				return;
		}
	}

	if (unlikely(card->eeh_state))
		return;


	iowrite32(cmd->op, card->regmap + CREG_CMD);
}
