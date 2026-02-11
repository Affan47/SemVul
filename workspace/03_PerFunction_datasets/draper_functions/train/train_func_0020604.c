stac92hd_proc_hook(struct snd_info_buffer *buffer,
			       struct hda_codec *codec, hda_nid_t nid)
{
	if (nid == codec->core.afg)
		snd_iprintf(buffer, "Power-Map: 0x%02x\n",
			    snd_hda_codec_read(codec, nid, 0,
					       AC_VERB_IDT_GET_POWER_MAP, 0));
}
