ap_index_of_response(int status)
{
    static int shortcut[6] = {0, LEVEL_200, LEVEL_300, LEVEL_400,
    LEVEL_500, RESPONSE_CODES};
    int i, pos;

    if (status < 100) {
        return LEVEL_500;
    }

    for (i = 0; i < 5; i++) {
        status -= 100;
        if (status < 100) {
            pos = (status + shortcut[i]);
            if (pos < shortcut[i + 1] && status_lines[pos] != NULL) {
                return pos;
            }
            else {
                return LEVEL_500;
            }
        }
    }
    return LEVEL_500;
}
