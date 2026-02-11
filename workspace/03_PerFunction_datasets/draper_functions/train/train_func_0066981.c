huawei_send_receive(const char *cmd)
{
    int run, bytes_send, recv_seq;
    char *tmp;
    static char reply[RECV_BUFFER_SIZE];


    bytes_send = huawei_send(cmd);


    strcpy(reply, "");

    if (bytes_send > 0) {

	recv_seq = 0;


	for (run = 0; run < 3; run++) {

	    tmp = huawei_receive();


	    if (strncmp(cmd, INIT_STRING, strlen(INIT_STRING)) == 0) {


		if (recv_seq == 0 && strncmp(tmp, INIT_STRING, strlen(INIT_STRING)) == 0) {
		    recv_seq = 1;
		}


		else if (recv_seq == 1 && strncmp(tmp, "OK", 2) == 0) {
		    strncpy(reply, tmp, sizeof(reply) - 1);
		    break;
		}


		else if (recv_seq == 1 && huawei_recv_error(tmp) == 1) {
		    strncpy(reply, tmp, sizeof(reply) - 1);
		    break;
		}


	    } else {


		if (recv_seq == 0 && strncmp(tmp, cmd, strlen(cmd)) == 0) {
		    recv_seq = 1;
		}


		else if (recv_seq == 1 && strlen(tmp) > 0 && huawei_recv_error(tmp) == 0) {
		    recv_seq = 2;
		    strncpy(reply, tmp, sizeof(reply) - 1);
		}


		else if (recv_seq == 2 && strncmp(tmp, "OK", 2) == 0) {
		    break;
		}


		else if (recv_seq == 1 && huawei_recv_error(tmp) == 1) {
		    strncpy(reply, tmp, sizeof(reply) - 1);
		    break;
		}
	    }
	}
    }

    return (reply);
}
