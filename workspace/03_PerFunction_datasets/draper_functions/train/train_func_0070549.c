ftp_pasv(struct stream_t *stream,int *newsock)
{
    struct stream_ctrl_t *stream_ctrl = stream->stream_ctrl;
    struct ftp_response_t *ftp_response;
    int data_sock = 0;
    int status_code;

    ftp_send_command(stream,"PASV\n");

    ftp_response = new_ftp_response_t();
    status_code = ftp_recv_response(stream,ftp_response);
    if(!is_ftp_OK(status_code)) {

	stream_ctrl->ftp_ctrl->mode = ACTIVE_FTP;
	free_ftp_response_t(ftp_response);
	*newsock = 0;
	return status_code;
    }
    else {
	char connect_host[INET6_ADDRSTRLEN + 4];

	int pasvport;
	int i;
	int value[6] = {0,0,0,0,0,0};
	char *line = ftp_response->lines->p;
	char *p;

	p = strrchr(line,',');
	if(p) {
	    for( ; (p >= line) && (isdigit(*p) || *p == ',') ; p--);
	    if(p <= line) {
		free_ftp_response_t(ftp_response);
		return 0;
	    }
	    p++;

	    for(i = 0; i < 6 ; i++) {
		value[i] = 0;
		for(; p && *p && isdigit(*p) ; p++) {
		    value[i] *= 10;
		    value[i] += *p - '0';
		}
		value[i] &= 0xff;
		if(!p || !(*p)) {
		    break;
		}
		else {
		    p++;
		}
	    }

	    if(p && *p) {
		snprintf(connect_host,sizeof(connect_host) - 1,
		         "%d.%d.%d.%d",value[0],value[1],value[2],value[3]);
		pasvport = (value[4] << 8) + value[5];
		data_sock = server_connect(connect_host,pasvport);
		free_ftp_response_t(ftp_response);
		*newsock = data_sock;
		return status_code;
	    }
	}
    }


    display(MSDL_ERR,"cannot get port number from recv reply\n");
    stream_ctrl->ftp_ctrl->mode = ACTIVE_FTP;
    free_ftp_response_t(ftp_response);
    *newsock = 0;
    return status_code;
}
