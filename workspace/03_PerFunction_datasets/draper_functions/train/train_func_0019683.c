_comedi_trigger(comedi_t *it,comedi_trig *t)
{
	if(!valid_dev(it) || !t)
		return -1;

	return comedi_ioctl(it->fd, COMEDI_TRIG, t);
}
