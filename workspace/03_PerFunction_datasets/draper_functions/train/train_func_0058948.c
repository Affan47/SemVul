send_info(int id, const MesgInfo* message) {
    int ret = msgsnd(id, message, sizeof(int), 0);
    if (ret == -1)
        syserr("msgsnd");
    return ret;
}
