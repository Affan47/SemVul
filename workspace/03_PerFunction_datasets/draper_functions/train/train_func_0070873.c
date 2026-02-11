vdr_dump_service_parameter_set (FILE *f, service_t *s, transponder_t *t, char *orbital_pos_override, int dump_channum, int dump_provider, int ca_select)
{
	int i;

	if ((s->video_pid || s->audio_pid[0]) && ((ca_select == -1) || (ca_select < 0) || (ca_select > 0) || ((ca_select == 0) && (s->scrambled == 0)))) {
		if ((dump_channum == 1) && (s->channel_num > 0))
			fprintf(f, ":@%i\n", s->channel_num);

		if (dump_provider == 1) {
			fprintf (f, "%s - ", s->provider_name);
		}
		fprintf (f, "%s;%s:", s->service_name, s->provider_name?s->provider_name:"");

		vdr_dump_dvb_parameters (f, t, orbital_pos_override);

		if ((s->pcr_pid != s->video_pid) && (s->video_pid > 0))
			fprintf (f, "%i+%i:", s->video_pid, s->pcr_pid);
		else
			fprintf (f, "%i:", s->video_pid);

		fprintf (f, "%i", s->audio_pid[0]);

		if (s->audio_lang && s->audio_lang[0][0])
			fprintf (f, "=%.4s", s->audio_lang[0]);

		for (i = 1; i < s->audio_num; i++)
		{
			fprintf (f, ",%i", s->audio_pid[i]);
			if (s->audio_lang && s->audio_lang[i][0])
				fprintf (f, "=%.4s", s->audio_lang[i]);
		}

		if (s->ac3_pid)
		{
			fprintf (f, ";%i", s->ac3_pid);
			if (s->audio_lang && s->audio_lang[0][0])
				fprintf (f, "=%.4s", s->audio_lang[0]);
		}

		fprintf (f, ":%d:", s->teletext_pid);


		if(ca_select == -1 || ca_select == 0) {
			fprintf (f, "0");
		}

		else if(ca_select == -2) {
			fprintf (f, "%X", s->ca_id[0]);
			for (i = 1; i < s->ca_num; i++) {
				if (s->ca_id[i] == 0) continue;
				fprintf (f, ",%X", s->ca_id[i]);
			}
		}

		else {
			fprintf (f, "%d", ca_select);
		}

		fprintf (f, ":%d:%d:%d:0", s->service_id, t->original_network_id, t->transport_stream_id);

		fprintf (f, "\n");
	}
}
