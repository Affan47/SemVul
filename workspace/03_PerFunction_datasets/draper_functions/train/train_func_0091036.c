ca0132_unsol_hp_delayed(struct work_struct *work)
{
	struct ca0132_spec *spec = container_of(
		to_delayed_work(work), struct ca0132_spec, unsol_hp_work);
	struct hda_jack_tbl *jack;

	ca0132_select_out(spec->codec);
	jack = snd_hda_jack_tbl_get(spec->codec, spec->unsol_tag_hp);
	if (jack) {
		jack->block_report = 0;
		snd_hda_jack_report_sync(spec->codec);
	}
}
