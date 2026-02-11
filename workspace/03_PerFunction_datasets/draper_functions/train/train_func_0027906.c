efm32_i2c_send_next_byte(struct efm32_i2c_ddata *ddata)
{
	struct i2c_msg *cur_msg = &ddata->msgs[ddata->current_msg];

	if (ddata->current_word >= cur_msg->len) {

		ddata->current_word = 0;
		ddata->current_msg += 1;

		if (ddata->current_msg >= ddata->num_msgs) {
			efm32_i2c_write32(ddata, REG_CMD, REG_CMD_STOP);
			complete(&ddata->done);
		} else {
			efm32_i2c_send_next_msg(ddata);
		}
	} else {
		efm32_i2c_write32(ddata, REG_TXDATA,
				cur_msg->buf[ddata->current_word++]);
	}
}
