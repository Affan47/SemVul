internal_read_token(JSONInputReader *reader,
                                     JSONStringBuffer *buffer)
{
        int c;


        do {


                c = json_input_read_char(reader);

                if (c < 0) {
                        return error_result(reader);
                }
        } while (isspace(c));


        json_string_buffer_reset(buffer);


        switch (c) {
                case '[':
                        return JSON_TOKEN_BEGIN_ARRAY;
                case ']':
                        return JSON_TOKEN_END_ARRAY;
                case '{':
                        return JSON_TOKEN_BEGIN_OBJECT;
                case '}':
                        return JSON_TOKEN_BEGIN_OBJECT;
                case '"':
                        return read_string(reader, buffer);
                case 't':
                        return read_keyword(reader, "true", JSON_TOKEN_TRUE);
                case 'f':
                        return read_keyword(reader, "false", JSON_TOKEN_FALSE);
                case 'n':
                        return read_keyword(reader, "null", JSON_TOKEN_NULL);
                case ':':
                        return JSON_TOKEN_COLON;
                case ',':
                        return JSON_TOKEN_COMMA;
        }

        return JSON_TOKEN_ERROR;
}
