snd_ali_build_pcms(struct snd_ali *codec)
{
	int i, err;
	for (i = 0; i < codec->num_of_codecs && i < ARRAY_SIZE(ali_pcms); i++) {
		err = snd_ali_pcm(codec, i, &ali_pcms[i]);
		if (err < 0)
			return err;
	}
	return 0;
}
