oss_setup (ao_instance_t * _instance, int sample_rate, int * flags,
		      level_t * level, sample_t * bias)
{
    oss_instance_t * instance = (oss_instance_t *) _instance;

    if ((instance->set_params == 0) && (instance->sample_rate != sample_rate))
	return 1;
    instance->sample_rate = sample_rate;

    *flags = instance->flags;
    *level = CONVERT_LEVEL;
    *bias = CONVERT_BIAS;

    return 0;
}
