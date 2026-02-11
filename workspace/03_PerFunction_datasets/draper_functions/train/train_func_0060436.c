snd_pcm_route_dump(snd_pcm_t *pcm, snd_output_t *out)
{
	snd_pcm_route_t *route = pcm->private_data;
	unsigned int dst;
	if (route->sformat == SND_PCM_FORMAT_UNKNOWN)
		snd_output_printf(out, "Route conversion PCM\n");
	else
		snd_output_printf(out, "Route conversion PCM (sformat=%s)\n",
			snd_pcm_format_name(route->sformat));
	snd_output_puts(out, "  Transformation table:\n");
	for (dst = 0; dst < route->params.ndsts; dst++) {
		snd_pcm_route_ttable_dst_t *d = &route->params.dsts[dst];
		unsigned int src;
		snd_output_printf(out, "    %d <- ", dst);
		if (d->nsrcs == 0) {
			snd_output_printf(out, "none\n");
			continue;
		}
		src = 0;
		while (1) {
			snd_pcm_route_ttable_src_t *s = &d->srcs[src];
			if (d->att)
#if SND_PCM_PLUGIN_ROUTE_FLOAT
				snd_output_printf(out, "%d*%g", s->channel, s->as_float);
#else
				snd_output_printf(out, "%d*%g", s->channel, (double)s->as_int / (double)SND_PCM_PLUGIN_ROUTE_RESOLUTION);
#endif
			else
				snd_output_printf(out, "%d", s->channel);
			src++;
			if (src == d->nsrcs)
				break;
			snd_output_puts(out, " + ");
		}
		snd_output_putc(out, '\n');
	}
	if (pcm->setup) {
		snd_output_printf(out, "Its setup is:\n");
		snd_pcm_dump_setup(pcm, out);
	}
	snd_output_printf(out, "Slave: ");
	snd_pcm_dump(route->plug.gen.slave, out);
}
