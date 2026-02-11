ProcessByte(jack_nframes_t time,
                                        jack_midi_data_t byte)
{
    if (byte >= 0xf8) {

        if (byte == 0xfd) {
            HandleInvalidStatusByte(byte);
            return false;
        }
        return PrepareByteEvent(time, byte);
    }
    if (byte == 0xf7) {

        if (status_byte == 0xf0) {
            RecordByte(byte);
            return PrepareBufferedEvent(time);
        }
        HandleUnexpectedSysexEnd(total_bytes);
        Clear();
        expected_bytes = 0;
        status_byte = 0;
        return false;
    }
    if (byte >= 0x80) {

        if (total_bytes) {
            HandleIncompleteMessage(total_bytes);
            Clear();
        }
        status_byte = byte;
        switch (byte & 0xf0) {
        case 0x80:
        case 0x90:
        case 0xa0:
        case 0xb0:
        case 0xe0:

            expected_bytes = 3;
            break;
        case 0xc0:
        case 0xd0:

            expected_bytes = 2;
            break;
        case 0xf0:
            switch (byte) {
            case 0xf0:

                expected_bytes = 0;
                break;
            case 0xf1:
            case 0xf3:

                expected_bytes = 2;
                break;
            case 0xf2:

                expected_bytes = 3;
                break;
            case 0xf4:
            case 0xf5:

                HandleInvalidStatusByte(byte);
                expected_bytes = 0;
                status_byte = 0;
                return false;
            case 0xf6:

                bool result = PrepareByteEvent(time, byte);
                if (result) {
                    expected_bytes = 0;
                    status_byte = 0;
                }
                return result;
            }
        }
        RecordByte(byte);
        return false;
    }

    if (! status_byte) {

        total_bytes++;
        unbuffered_bytes++;
        return false;
    }
    if (! total_bytes) {

        RecordByte(status_byte);
    }
    RecordByte(byte);
    return (total_bytes == expected_bytes) ? PrepareBufferedEvent(time) :
        false;
}
