snd_hda_codec_amp_init(struct hda_codec *codec, hda_nid_t nid, int ch,
			   int dir, int idx, int mask, int val)
{
	int orig;

	if (!codec->core.regmap)
		return -EINVAL;
	regcache_cache_only(codec->core.regmap, true);
	orig = snd_hda_codec_amp_read(codec, nid, ch, dir, idx);
	regcache_cache_only(codec->core.regmap, false);
	if (orig >= 0)
		return 0;
	return snd_hda_codec_amp_update(codec, nid, ch, dir, idx, mask, val);
}
