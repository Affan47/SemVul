writeToFrontEnd(const char *buf)
{
    int n = write(sockfd_fe, buf,strlen(buf));
    if (n < 0) {
        logger(L_ERR, "ERROR writing to frontend");
    }
    return;
}
