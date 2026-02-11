focaltech_read_size(struct psmouse *psmouse)
{
	struct ps2dev *ps2dev = &psmouse->ps2dev;
	struct focaltech_data *priv = psmouse->private;
	char param[3];

	if (focaltech_read_register(ps2dev, 2, param))
		return -EIO;


	priv->x_max = (unsigned char)param[1] * 128;
	priv->y_max = (unsigned char)param[2] * 128;

	return 0;
}
