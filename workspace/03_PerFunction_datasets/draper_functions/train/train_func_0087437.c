saa7164_s_input(struct saa7164_port *port, unsigned int i)
{
	struct saa7164_dev *dev = port->dev;

	dprintk(DBGLVL_ENC, "%s() input=%d\n", __func__, i);

	if (i >= 7)
		return -EINVAL;

	port->mux_input = i + 1;

	if (saa7164_api_set_videomux(port) != SAA_OK)
		return -EIO;

	return 0;
}
