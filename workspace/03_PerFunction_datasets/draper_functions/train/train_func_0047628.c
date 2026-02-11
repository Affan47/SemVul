biscDefineSong(unsigned char songNum, unsigned char *notes, unsigned char *notesDurations, unsigned int notesLen) {
    if(songNum > BISC_MAX_SONG_NUM)                   return BISC_ERR;
    if(sizeof(notes) != sizeof(notesDurations))       return BISC_ERR;
    if(notesLen <= 0 || notesLen > BISC_MAX_SONG_LEN) return BISC_ERR;

    if(biscSendByte(BISC_CMD_SONG_DEFINE) == BISC_ERR) return BISC_ERR;
    if(biscSendByte(songNum)              == BISC_ERR) return BISC_ERR;
    if(biscSendByte(notesLen)             == BISC_ERR) return BISC_ERR;

    for(unsigned int i=0; i<notesLen; i++) {
        if(notes[i] < BISC_MIN_NOTE || notes[i] > BISC_MAX_NOTE) return BISC_ERR;

        if(biscSendByte(notes[i])          == BISC_ERR) return BISC_ERR;
        if(biscSendByte(notesDurations[i]) == BISC_ERR) return BISC_ERR;
    }

    return BISC_SUCCESS;
}
