mp4ff_close(mp4ff_t *ff)
{
    int32_t i;

    for (i = 0; i < ff->total_tracks; i++)
    {
        if (ff->track[i])
        {
            if (ff->track[i]->stsz_table)
                free(ff->track[i]->stsz_table);
            if (ff->track[i]->stts_sample_count)
                free(ff->track[i]->stts_sample_count);
            if (ff->track[i]->stts_sample_delta)
                free(ff->track[i]->stts_sample_delta);
            if (ff->track[i]->stsc_first_chunk)
                free(ff->track[i]->stsc_first_chunk);
            if (ff->track[i]->stsc_samples_per_chunk)
                free(ff->track[i]->stsc_samples_per_chunk);
            if (ff->track[i]->stsc_sample_desc_index)
                free(ff->track[i]->stsc_sample_desc_index);
            if (ff->track[i]->stco_chunk_offset)
                free(ff->track[i]->stco_chunk_offset);
            if (ff->track[i]->decoderConfig)
                free(ff->track[i]->decoderConfig);
			if (ff->track[i]->ctts_sample_count)
				free(ff->track[i]->ctts_sample_count);
			if (ff->track[i]->ctts_sample_offset)
				free(ff->track[i]->ctts_sample_offset);
#ifdef ITUNES_DRM
            if (ff->track[i]->p_drms)
                drms_free(ff->track[i]->p_drms);
#endif
            free(ff->track[i]);
        }
    }

#ifdef USE_TAGGING
    mp4ff_tag_delete(&(ff->tags));
#endif

    if (ff) free(ff);
}
