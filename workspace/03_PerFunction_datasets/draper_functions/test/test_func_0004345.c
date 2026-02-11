sst_set_pipe_gain(struct sst_ids *ids,
			struct sst_data *drv, int mute)
{
	int ret = 0;
	struct sst_gain_mixer_control *mc;
	struct sst_gain_value *gv;
	struct sst_module *gain = NULL;

	list_for_each_entry(gain, &ids->gain_list, node) {
		struct snd_kcontrol *kctl = gain->kctl;

		dev_dbg(&drv->pdev->dev, "control name=%s\n", kctl->id.name);
		mc = (void *)kctl->private_value;
		gv = mc->gain_val;

		ret = sst_send_gain_cmd(drv, gv, mc->task_id,
			mc->pipe_id | mc->instance_id, mc->module_id, mute);
		if (ret)
			return ret;
	}
	return ret;
}
