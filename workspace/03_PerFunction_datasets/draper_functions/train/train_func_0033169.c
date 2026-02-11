ois_encode_deliver_sm_result(char *str, int result)
{
    char raw[4];

    SAY(3, "ois_encode_deliver_sm_result");


    raw[0] = (char) result;

    return ois_convert_to_ia5(str, raw, 1);
}
