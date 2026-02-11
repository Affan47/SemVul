hermesi_program_end(struct hermes *hw)
{
	struct hermes_response resp;
	int rc = 0;
	int err;

	rc = hw->ops->cmd_wait(hw, HERMES_PROGRAM_DISABLE, 0, &resp);

	pr_debug("PROGRAM_DISABLE returned %d, "
		 "r0 0x%04x, r1 0x%04x, r2 0x%04x\n",
		 rc, resp.resp0, resp.resp1, resp.resp2);

	if ((rc == 0) &&
	    ((resp.status & HERMES_STATUS_CMDCODE) != HERMES_CMD_DOWNLD))
		rc = -EIO;

	err = hermes_aux_control(hw, 0);
	pr_debug("AUX disable returned %d\n", err);


	hermes_write_regn(hw, EVACK, 0xFFFF);


	(void) hw->ops->init_cmd_wait(hw, 0x0000 | HERMES_CMD_INIT,
				      0, 0, 0, NULL);

	return rc ? rc : err;
}
