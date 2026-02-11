snd_ice1712_akm4xxx_init(struct snd_akm4xxx *ak, const struct snd_akm4xxx *temp,
			     const struct snd_ak4xxx_private *_priv, struct snd_ice1712 *ice)
{
	struct snd_ak4xxx_private *priv;

	if (_priv != NULL) {
		priv = kmalloc(sizeof(*priv), GFP_KERNEL);
		if (priv == NULL)
			return -ENOMEM;
		*priv = *_priv;
	} else {
		priv = NULL;
	}
	*ak = *temp;
	ak->card = ice->card;
        ak->private_value[0] = (unsigned long)priv;
	ak->private_data[0] = ice;
	if (ak->ops.lock == NULL)
		ak->ops.lock = snd_ice1712_akm4xxx_lock;
	if (ak->ops.unlock == NULL)
		ak->ops.unlock = snd_ice1712_akm4xxx_unlock;
	if (ak->ops.write == NULL)
		ak->ops.write = snd_ice1712_akm4xxx_write;
	snd_akm4xxx_init(ak);
	return 0;
}
