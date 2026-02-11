get_error_code(int no) {
    while (no >= ERR_MESSAGE_MIN && no <= ERR_MESSAGE_MAX) {
        ErrorMessage * m = msgs + (no - ERR_MESSAGE_MIN);
        switch (m->source) {
        case SRC_REPORT:
        case SRC_MESSAGE:
            no = m->error;
            continue;
        }
        return ERR_OTHER;
    }
    return no;
}
