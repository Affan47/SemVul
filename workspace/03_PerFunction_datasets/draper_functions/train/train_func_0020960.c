snd_hda_spdif_ctls_assign(struct hda_codec *codec, int idx, hda_nid_t nid)
{
	struct hda_spdif_out *spdif;
	unsigned short val;

	mutex_lock(&codec->spdif_mutex);
	spdif = snd_array_elem(&codec->spdif_out, idx);
	if (spdif->nid != nid) {
		spdif->nid = nid;
		val = spdif->ctls;
		set_spdif_ctls(codec, nid, val & 0xff, (val >> 8) & 0xff);
	}
	mutex_unlock(&codec->spdif_mutex);
}
