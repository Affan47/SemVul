pymelem_init(struct pymelem *pymelem, PyObject *args, PyObject *kwds ATTRIBUTE_UNUSED)
{
	char *name;
	long index, weight;
	snd_mixer_selem_id_t *id;
	int err;

	if (!PyArg_ParseTuple(args, "Osii", &pymelem->py_mixer, &name, &index, &weight))
		return -1;
	memset(&pymelem->selem, 0, sizeof(pymelem->selem));
	if (snd_mixer_selem_id_malloc(&id))
		return -1;
	snd_mixer_selem_id_set_name(id, name);
	snd_mixer_selem_id_set_index(id, index);
	pymelem->selem.id = id;
	pymelem->selem.ops = &simple_python_ops;
	err = snd_mixer_elem_new(&pymelem->melem, SND_MIXER_ELEM_SIMPLE,
				 weight, &pymelem->selem, selem_free);
	if (err < 0) {
		snd_mixer_selem_id_free(id);
		return -1;
	}
	return 0;
}
