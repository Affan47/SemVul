mp3tunes_harmony_download_deinit(mp3tunes_harmony_download_t **harmony_download) {
    mp3tunes_harmony_download_t* hd = *harmony_download;
    if (hd->file_key) { free(hd->file_key); }
    if (hd->file_name) { free(hd->file_name); }
    if (hd->file_format) { free(hd->file_format); }

    if (hd->artist_name) { free(hd->artist_name); }
    if (hd->album_title) { free(hd->album_title); }
    if (hd->track_title) { free(hd->track_title); }

    if (hd->device_bitrate) { free(hd->device_bitrate); }
    if (hd->file_bitrate) { free(hd->file_bitrate); }

    if (hd->url) { free(hd->url); }
    free(hd);
    return TRUE;
}
