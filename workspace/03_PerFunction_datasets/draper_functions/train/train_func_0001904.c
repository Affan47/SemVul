cc_free(CyanChat** cc) {
    if (*cc == NULL) {
        return;
    }

    if ((*cc)->socket != -1) {
        cc_send_logout(*cc);

        shutdown((*cc)->socket, SHUT_RDWR);
        close((*cc)->socket);
        (*cc)->socket = -1;
    }

    if ((*cc)->tmp_nickname != NULL) {
        free((*cc)->tmp_nickname);
    }

    if ((*cc)->nickname != NULL) {
        free((*cc)->nickname);
    }

    free(*cc);
    *cc = NULL;
}
