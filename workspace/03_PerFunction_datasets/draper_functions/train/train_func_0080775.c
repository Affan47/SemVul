json_input_read_char(JSONInputReader *reader)
{
        unsigned char charbuf[4];
        int len;
        int err;
        int c;
        int i;


        if (reader->encoding == JSON_ENCODING_UNKNOWN) {
                err = json_input_find_encoding(reader);

                if (err < 0) {
                        return err;
                }
        }


        if (reader->encoding == JSON_ENCODING_UTF8) {
                return json_input_read_utf8(reader);
        }


        len = encoding_lengths[reader->encoding];

        for (i=0; i<len; ++i) {
                c = json_input_read_byte(reader);

                if (c < 0) {
                        return c;
                }

                charbuf[i] = c;
        }


        switch (reader->encoding) {
                case JSON_ENCODING_16LE:
                        return (charbuf[1] << 8) | charbuf[0];
                case JSON_ENCODING_16BE:
                        return (charbuf[0] << 8) | charbuf[1];
                case JSON_ENCODING_32LE:
                        return (charbuf[3] << 24)
                             | (charbuf[2] << 16)
                             | (charbuf[1] << 8)
                             | charbuf[0];
                case JSON_ENCODING_32BE:
                        return (charbuf[0] << 24)
                             | (charbuf[1] << 16)
                             | (charbuf[2] << 8)
                             | charbuf[3];
                default:
                        return JSON_ERROR_ENCODING;
        }
}
