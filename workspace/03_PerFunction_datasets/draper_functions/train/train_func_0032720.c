pt2258_switch_put(struct snd_kcontrol *kcontrol,
			     struct snd_ctl_elem_value *ucontrol)
{
	struct snd_pt2258 *pt = kcontrol->private_data;
	unsigned char bytes[2];
	int val;

	val = !ucontrol->value.integer.value[0];
	if (pt->mute == val)
		return 0;

	pt->mute = val;
	bytes[0] = val ? PT2258_CMD_MUTE : PT2258_CMD_UNMUTE;
	snd_i2c_lock(pt->i2c_bus);
	if (snd_i2c_sendbytes(pt->i2c_dev, bytes, 1) != 1)
		goto __error;
	snd_i2c_unlock(pt->i2c_bus);

	return 1;

      __error:
	snd_i2c_unlock(pt->i2c_bus);
	snd_printk(KERN_ERR "PT2258 access failed 2\n");
	return -EIO;
}
