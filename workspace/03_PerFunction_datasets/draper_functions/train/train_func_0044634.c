wmserver_announce_continue(struct stream_t *stream)
{
    struct stream_ctrl_t *stream_ctrl = stream->stream_ctrl;
    struct rtsp_ctrl_t *rtsp_ctrl = stream_ctrl->rtsp_ctrl;

    int i = 0;
    char checkbuf[10];
    struct rtsp_header_t *rtsp_hdr = NULL;
    int got_cseq = 0;
    int status_code = 0;
    char *field = NULL;
    int len = 0;
    char *description = NULL;
    char *buffer = NULL;

    struct sdpwms_t *sdpwms = NULL;
    struct asf_headerinfo_t* asf_headerinfo = NULL;


    buffer = xmalloc(BUFSIZE_1K);

    i = recv_data(stream,checkbuf,8);

    if(i < 8 || memcmp(checkbuf,"ANNOUNCE",8)) {
	goto failed;
    }

    stream_data_push_back(stream,checkbuf,i);

    rtsp_hdr = new_rtsp_header();
    rtsp_recv_header(stream,rtsp_hdr);

    status_code = rtsp_hdr->status_code;

    if((field = rtsp_get_field(rtsp_hdr,"Content-Length")) != NULL) {
	while(*field == ' ') field++;
	len = atoi(field);
    }

    if((field = rtsp_get_field(rtsp_hdr,"Cseq")) != NULL) {
	while(*field == ' ') field++;
	got_cseq = atoi(field);
    }


    description = xmalloc(len + 1);
    len = read_data(stream,description,len);
    description[len] = '\0';

    free_rtsp_header(rtsp_hdr);

    if(status_code != RTSP_STATUS_ANNOUNCE) {
	goto failed;
    }


    rtsp_200ok(stream,got_cseq,rtsp_ctrl->session);


    wmserver_get_info_from_sdp_string(stream,description,&asf_headerinfo,&sdpwms);


    if(wmserver_rtsp_setup(stream,asf_headerinfo,sdpwms) < 0) {
	goto failed;
    }


    if(wmserver_rtsp_set_parameter(stream) < 0) {
	goto failed;
    }


    if(wmserver_rtsp_play(stream) < 0) {
	goto failed;
    }


    free_sdpwms_t(sdpwms);
    free(description);
    free(buffer);
    return asf_headerinfo;


  failed:
    if(description) free(description);
    if(sdpwms) free_sdpwms_t(sdpwms);
    if(asf_headerinfo) free_asf_headerinfo_t(asf_headerinfo);
    if(buffer) free(buffer);
    return NULL;

}
