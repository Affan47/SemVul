receiveByte(unsigned char byte) {

    switch (state) {
        case ST_WAIT_FOR_SYNC:
            if (byte == ANT_SYNC_BYTE) {
                state = ST_GET_LENGTH;
                checksum = ANT_SYNC_BYTE;
                rxMessage[0] = byte;
            }
            break;

        case ST_GET_LENGTH:
            if ((byte == 0) || (byte > ANT_MAX_LENGTH)) {
                state = ST_WAIT_FOR_SYNC;
            }
            else {
              rxMessage[ANT_OFFSET_LENGTH] = byte;
                checksum ^= byte;
                length = byte;
                bytes = 0;
                state = ST_GET_MESSAGE_ID;
            }
            break;

        case ST_GET_MESSAGE_ID:
            rxMessage[ANT_OFFSET_ID] = byte;
            checksum ^= byte;
            state = ST_GET_DATA;
            break;

        case ST_GET_DATA:
            rxMessage[ANT_OFFSET_DATA + bytes] = byte;
            checksum ^= byte;
            if (++bytes >= length){
                state = ST_VALIDATE_PACKET;
            }
            break;

        case ST_VALIDATE_PACKET:
            if (checksum == byte){
                processMessage();
            }
            state = ST_WAIT_FOR_SYNC;
            break;
    }
}
