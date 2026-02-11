speakup_lock(struct vc_data *vc)
{
	if (!spk_key_locked)
		spk_key_locked = key_speakup = 16;
	else
		spk_key_locked = key_speakup = 0;
}
