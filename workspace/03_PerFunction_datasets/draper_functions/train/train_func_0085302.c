ApplyRunningStatus(size_t *size, jack_midi_data_t **buffer,
                         jack_midi_data_t running_status)
{


    jack_midi_data_t status = **buffer;
    if ((status >= 0x80) && (status < 0xf0)) {
        if (status == running_status) {
            (*buffer)++;
            (*size)--;
        } else {
            running_status = status;
        }
    } else if (status < 0xf8) {
        running_status = 0;
    }
    return running_status;
}
