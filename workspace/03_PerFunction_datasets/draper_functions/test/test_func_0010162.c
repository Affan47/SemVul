main_loop(void)
{
        fd_set rfds, cfds;
        int retval, ret1, ret2, ret3;

        while(!reset) {
                retval = ret1 = ret2 = ret3 = 0;
                FD_ZERO(&rfds);
                conn_get_fds(&rfds);
                FD_ZERO(&cfds);
                conn_get_connecting_fds(&cfds);

                retval = select(FD_SETSIZE, &rfds, &cfds, NULL, NULL);
                diag(COMPONENT, DIAG_DEBUG, "main_loop: select returned %d", retval);
                if (retval < 0) {
                        diag(COMPONENT, DIAG_ERROR, "main_loop: select: %s", strerror(errno));
                        break;
                }
                if (retval == 0) {

                        continue;
                }
                if (FD_ISSET(lec_params.kernel->fd, &rfds)) {
                        ret1 = msg_from_kernel();
                        FD_CLR(lec_params.kernel->fd, &rfds);
                }
                ret2 = complete_connections(&cfds);
                ret3 = check_connections(&rfds);

                if (ret1 < 0 || ret2 < 0 || ret3 < 0)
                        break;
        }

        diag(COMPONENT, DIAG_DEBUG, "exiting main_loop");

        return;
}
