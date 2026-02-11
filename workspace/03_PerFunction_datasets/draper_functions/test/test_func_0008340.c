lx_pipe_start(struct lx6464es *chip, u32 pipe, int is_capture)
{
	int err;

	err = lx_pipe_wait_for_idle(chip, pipe, is_capture);
	if (err < 0)
		return err;

	err = lx_pipe_toggle_state(chip, pipe, is_capture);

	return err;
}
