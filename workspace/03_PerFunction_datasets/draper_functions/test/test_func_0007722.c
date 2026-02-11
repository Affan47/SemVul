pymixer_init(struct pymixer *pymixer, PyObject *args, PyObject *kwds ATTRIBUTE_UNUSED)
{
	long class, mixer;

	if (!PyArg_ParseTuple(args, "iiO", &class, &mixer, &pymixer->mdict))
		return -1;
	pymixer->class = (snd_mixer_class_t *)class;
	pymixer->mixer = (snd_mixer_t *)mixer;
	pymixer->hctl_count = 0;
	pymixer->hctl = NULL;
	pymixer->helem_count = 0;
	pymixer->helem = NULL;
	pymixer->melem_count = 0;
	pymixer->melem = NULL;
	return 0;
}
