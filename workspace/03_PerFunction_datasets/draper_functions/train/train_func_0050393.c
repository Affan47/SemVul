qsocket_close(int sockfd, int timeoutms) {

    if (timeoutms >= 0 && shutdown(sockfd, SHUT_WR) == 0) {
        char buf[1024];
        while (true) {
            ssize_t read = qio_read(sockfd, buf, sizeof(buf), timeoutms);
            if (read <= 0)
                break;DEBUG("Throw %zu bytes from dummy input stream.", read);
        }
    }

    if (close(sockfd) == 0)
        return true;
    return false;
}
