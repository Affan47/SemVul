adsi_add_field(adsi_tx_state_t *s, uint8_t *msg, int len, uint8_t field_type, uint8_t const *field_body, int field_len)
{
    int i;
    int x;

    switch (s->standard)
    {
    case ADSI_STANDARD_CLASS:
    case ADSI_STANDARD_CLIP:
    case ADSI_STANDARD_ACLIP:

        if (len <= 0)
        {

            msg[0] = field_type;
            msg[1] = 0;
            len = 2;
        }
        else
        {

            if (field_type)
            {
                msg[len++] = field_type;
                msg[len++] = (uint8_t) field_len;
                if (field_len == DLE)
                    msg[len++] = (uint8_t) field_len;
                memcpy(msg + len, field_body, field_len);
                len += field_len;
            }
            else
            {

                memcpy(msg + len, field_body, field_len);
                len += field_len;
            }
        }
        break;
    case ADSI_STANDARD_JCLIP:


        if (len <= 0)
        {

            msg[0] = field_type;
            msg[1] = 0;
            len = 2;
        }
        else
        {

            msg[len++] = field_type;
            if (field_type == DLE)
                msg[len++] = field_type;
            msg[len++] = (uint8_t) field_len;
            if (field_len == DLE)
                msg[len++] = (uint8_t) field_len;
            for (i = 0;  i < field_len;  i++)
            {
                msg[len++] = field_body[i];
                if (field_body[i] == DLE)
                    msg[len++] = field_body[i];
            }
        }
        break;
    case ADSI_STANDARD_CLIP_DTMF:
        if (len <= 0)
        {

            msg[0] = field_type;
            len = 1;
        }
        else
        {

            x = msg[--len];
            if (field_type != CLIP_DTMF_HASH_UNSPECIFIED)
                msg[len++] = field_type;
            memcpy(msg + len, field_body, field_len);
            msg[len + field_len] = x;
            len += (field_len + 1);
        }
        break;
    case ADSI_STANDARD_TDD:
        if (len < 0)
            len = 0;
        for (i = 0;  i < field_len;  i++)
        {
            if ((x = adsi_encode_baudot(s, field_body[i])))
            {
                if ((x & 0x3E0))
                    msg[len++] = (uint8_t) ((x >> 5) & 0x1F);
                msg[len++] = (uint8_t) (x & 0x1F);
            }
        }
        break;
    }

    return len;
}
