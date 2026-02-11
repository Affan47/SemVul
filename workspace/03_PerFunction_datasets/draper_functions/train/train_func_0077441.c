cyapa_pip_irq_cmd_handler(struct cyapa *cyapa)
{
	struct cyapa_pip_cmd_states *pip = &cyapa->cmd_states.pip;
	int length;

	if (atomic_read(&pip->cmd_issued)) {

		if (pip->is_irq_mode == false)
			return false;


		cyapa_i2c_pip_read(cyapa, pip->irq_cmd_buf,
			PIP_RESP_LENGTH_SIZE);
		length = get_unaligned_le16(pip->irq_cmd_buf);
		length = (length <= PIP_RESP_LENGTH_SIZE) ?
				PIP_RESP_LENGTH_SIZE : length;
		if (length > PIP_RESP_LENGTH_SIZE)
			cyapa_i2c_pip_read(cyapa,
				pip->irq_cmd_buf, length);
		if (!(pip->resp_sort_func &&
			pip->resp_sort_func(cyapa,
				pip->irq_cmd_buf, length))) {


			length = 0;
			if (pip->resp_len)
				length = *pip->resp_len;
			cyapa_empty_pip_output_data(cyapa,
					pip->resp_data,
					&length,
					pip->resp_sort_func);
			if (pip->resp_len && length != 0) {
				*pip->resp_len = length;
				atomic_dec(&pip->cmd_issued);
				complete(&pip->cmd_ready);
			}
			return false;
		}

		if (pip->resp_data && pip->resp_len) {
			*pip->resp_len = (*pip->resp_len < length) ?
				*pip->resp_len : length;
			memcpy(pip->resp_data, pip->irq_cmd_buf,
				*pip->resp_len);
		}
		atomic_dec(&pip->cmd_issued);
		complete(&pip->cmd_ready);
		return false;
	}

	return true;
}
