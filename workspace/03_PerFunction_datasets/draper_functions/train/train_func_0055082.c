cddb_track_set_length(cddb_track_t *track, int length)
{
    cddb_track_t *prev;

    if (track && (length >= 0)) {
        track->length = length;

        if (track->disc && (track->frame_offset == -1)) {
            prev = track->prev;
            if (prev) {

                if ((prev->frame_offset != -1) && (prev->length != -1)) {
                    track->frame_offset = prev->frame_offset + SECONDS_TO_FRAMES(prev->length);
                }
            } else {

                track->frame_offset = 150;
            }
            cddb_log_debug("frame offset set to %d", track->frame_offset);
        }
    }
}
