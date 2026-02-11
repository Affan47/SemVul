snd_seq_oss_readq_puts(struct seq_oss_readq *q, int dev, unsigned char *data, int len)
{
	union evrec rec;
	int result;

	memset(&rec, 0, sizeof(rec));
	rec.c[0] = SEQ_MIDIPUTC;
	rec.c[2] = dev;

	while (len-- > 0) {
		rec.c[1] = *data++;
		result = snd_seq_oss_readq_put_event(q, &rec);
		if (result < 0)
			return result;
	}
	return 0;
}
