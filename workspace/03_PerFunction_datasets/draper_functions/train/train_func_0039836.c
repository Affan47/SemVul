encode_data_float(encoder_state *s, float **pcm, int samples)
{
    float **buf;
    int i;

    buf = vorbis_analysis_buffer(&s->vd, samples);

    for(i=0; i < s->vi.channels; i++)
    {
        memcpy(buf[i], pcm[i], samples*sizeof(float));
    }

    vorbis_analysis_wrote(&s->vd, samples);

    s->samples_in_current_page += samples;
}
