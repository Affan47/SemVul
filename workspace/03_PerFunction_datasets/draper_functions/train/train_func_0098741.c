mp3tunes_harmony_add_download_to_queue(MP3tunesHarmony *harmony, mp3tunes_harmony_download_t* harmony_download) {
    g_queue_push_tail(harmony->download_queue, harmony_download);
    if (harmony->sid_state == MP3TUNES_HARMONY_SID_STATE_NONE) {
        harmony_get_session_id(harmony);
    } else if (harmony->sid_state == MP3TUNES_HARMONY_SID_STATE_READY) {
        harmony_download->url = mp3tunes_locker_generate_download_url_from_file_key(harmony->mp3tunes_locker, harmony_download->file_key);
        download_ready_emit(harmony, harmony_download);
    }
}
