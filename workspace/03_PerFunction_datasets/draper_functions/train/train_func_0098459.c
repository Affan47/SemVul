check_credentials(struct ntb_ipc *ipc,
                  int sock)
{
        uid_t uid;

        if (!get_peer_uid(sock, &uid)) {
                ntb_log("Error getting credentials for IPC connection: %s",
                        strerror(errno));
                return false;
        }


        if (uid != 0 && uid != ipc->uid) {
                ntb_log("Rejecting IPC connection from unauthorized user %i",
                        uid);
                return false;
        }

        return true;
}
