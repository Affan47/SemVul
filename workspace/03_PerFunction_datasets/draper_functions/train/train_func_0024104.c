snd_pcm_route_write_areas(snd_pcm_t *pcm,
			  const snd_pcm_channel_area_t *areas,
			  snd_pcm_uframes_t offset,
			  snd_pcm_uframes_t size,
			  const snd_pcm_channel_area_t *slave_areas,
			  snd_pcm_uframes_t slave_offset,
			  snd_pcm_uframes_t *slave_sizep)
{
	snd_pcm_route_t *route = pcm->private_data;
	snd_pcm_t *slave = route->plug.gen.slave;
	if (size > *slave_sizep)
		size = *slave_sizep;
	snd_pcm_route_convert(slave_areas, slave_offset,
			      areas, offset,
			      pcm->channels,
			      slave->channels,
			      size, &route->params);
	*slave_sizep = size;
	return size;
}
