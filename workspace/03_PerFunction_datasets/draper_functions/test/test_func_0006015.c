rtsp_set_uri(struct rtsp_header_t *rtsp_hdr,const char *uri)
{
    if(rtsp_hdr == NULL || uri == NULL) return;
    rtsp_hdr->uri = xmalloc(strlen(uri) + 1);
    strcpy(rtsp_hdr->uri,uri);
}
