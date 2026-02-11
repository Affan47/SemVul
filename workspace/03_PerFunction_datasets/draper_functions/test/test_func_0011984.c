mov_write_stts_tag(ByteIOContext *pb, MOVTrack *track)
{
    MOVStts *stts_entries;
    uint32_t entries = -1;
    uint32_t atom_size;
    int i;

    if (track->enc->codec_type == CODEC_TYPE_AUDIO && !track->audio_vbr) {
        stts_entries = av_malloc(sizeof(*stts_entries));
        stts_entries[0].count = track->sampleCount;
        stts_entries[0].duration = 1;
        entries = 1;
    } else {
        stts_entries = av_malloc(track->entry * sizeof(*stts_entries));
        for (i=0; i<track->entry; i++) {
            int64_t duration = i + 1 == track->entry ?
                track->trackDuration - track->cluster[i].dts + track->cluster[0].dts :
                track->cluster[i+1].dts - track->cluster[i].dts;
            if (i && duration == stts_entries[entries].duration) {
                stts_entries[entries].count++;
            } else {
                entries++;
                stts_entries[entries].duration = duration;
                stts_entries[entries].count = 1;
            }
        }
        entries++;
    }
    atom_size = 16 + (entries * 8);
    put_be32(pb, atom_size);
    put_tag(pb, "stts");
    put_be32(pb, 0);
    put_be32(pb, entries);
    for (i=0; i<entries; i++) {
        put_be32(pb, stts_entries[i].count);
        put_be32(pb, stts_entries[i].duration);
    }
    av_free(stts_entries);
    return atom_size;
}
