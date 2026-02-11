msg_from_mps(int slot)
{
        int bytes_read, fd;
        char buff[MAX_PACKET_LENGTH];

        fd = fds[slot].fd;
        bytes_read = read(fd, buff, sizeof(buff));
        if (bytes_read < 0) {
                printf("mpcd: io.c: read failed from MPS: %s\n", strerror(errno));
                close(fd);
                fds[slot].fd = -1;
                socket_type[slot] = NOT_USED;
                return -1;
        }
        if (bytes_read == 0) {
                dprintf("mpcd: io.c: EOF from MPS\n");
                close(fd);
                fds[slot].fd = -1;
                if (slot == 1)
		        mpc_control.MPS_socket = -1;
                socket_type[slot] = NOT_USED;
                return 1;
        }

        if ( memcmp(buff, &llc_snap_mpoa_ctrl, sizeof(llc_snap_mpoa_ctrl)) != 0 ) {
                printf("mpcd: io.c: msg_from_mps: MPS is pushing us garbage\n");
                return -1;
        }

        (void)recognize_packet(buff + sizeof(struct llc_snap_hdr));

	return 0;
}
