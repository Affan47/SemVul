mp4ff_chunk_to_offset(const mp4ff_t *f, const int32_t track, const int32_t chunk)
{
    const mp4ff_track_t * p_track = f->track[track];

    if (p_track->stco_entry_count && (chunk > p_track->stco_entry_count))
    {
        return p_track->stco_chunk_offset[p_track->stco_entry_count - 1];
    } else if (p_track->stco_entry_count) {
        return p_track->stco_chunk_offset[chunk - 1];
    } else {
        return 8;
    }

    return 0;
}
