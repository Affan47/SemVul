speakup_bits(struct vc_data *vc)
{
	int val = this_speakup_key - (FIRST_EDIT_BITS - 1);

	if (spk_special_handler != NULL || val < 1 || val > 6) {
		synth_printf("%s\n", spk_msg_get(MSG_ERROR));
		return;
	}
	pb_edit = &spk_punc_info[val];
	synth_printf(spk_msg_get(MSG_EDIT_PROMPT), pb_edit->name);
	spk_special_handler = edit_bits;
}
