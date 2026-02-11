Poll(fd_set& in_rset, fd_set& in_wset) {
    int ret = 0;


	if (cli_fd < 0)
		return 0;

	if (connect_complete == 0) {

		if (FD_ISSET(cli_fd, &in_wset)) {
			int r, e;
			socklen_t l;

			e = 0;
			l = sizeof(int);

			r = getsockopt(cli_fd, SOL_SOCKET, SO_ERROR, &e, &l);


			if (r < 0 || e != 0) {

				if (connect_cb != NULL)
					(*connect_cb)(globalreg, e, connect_aux);


				KillConnection();

			} else {

				connect_complete = 1;
				cl_valid = 1;

				if (connect_cb != NULL)
					(*connect_cb)(globalreg, 0, connect_aux);

				return 0;
			}
		}

		return 0;
	}

    if (!cl_valid)
        return 0;


    if (FD_ISSET(cli_fd, &in_rset)) {

        if ((ret = ReadBytes()) < 0) {
            KillConnection();
            return ret;
		}


        if (ret != 0 && cliframework->ParseData() < 0) {
            KillConnection();
            return -1;
        }
    }

	if (cli_fd < 0 || !cl_valid) {
		KillConnection();
		return -1;
	}


    if (FD_ISSET(cli_fd, &in_wset)) {


        if ((ret = WriteBytes()) < 0)
            KillConnection();
            return ret;
    }

    return ret;
}
