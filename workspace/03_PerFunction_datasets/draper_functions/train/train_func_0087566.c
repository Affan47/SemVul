mp4ff_chunk_of_sample(const mp4ff_t *f, const int32_t track, const int32_t sample,
                              int32_t *chunk_sample, int32_t *chunk)
{
    int32_t total_entries = 0;
    int32_t chunk2entry;
    int32_t chunk1, chunk2, chunk1samples, range_samples, total = 0;

    if (f->track[track] == NULL)
    {
        return -1;
    }

    total_entries = f->track[track]->stsc_entry_count;

    chunk1 = 1;
    chunk1samples = 0;
    chunk2entry = 0;

    do
    {
        chunk2 = f->track[track]->stsc_first_chunk[chunk2entry];
        *chunk = chunk2 - chunk1;
        range_samples = *chunk * chunk1samples;

        if (sample < total + range_samples) break;

        chunk1samples = f->track[track]->stsc_samples_per_chunk[chunk2entry];
        chunk1 = chunk2;

        if(chunk2entry < total_entries)
        {
            chunk2entry++;
            total += range_samples;
        }
    } while (chunk2entry < total_entries);

    if (chunk1samples)
        *chunk = (sample - total) / chunk1samples + chunk1;
    else
        *chunk = 1;

    *chunk_sample = total + (*chunk - chunk1) * chunk1samples;

    return 0;
}
