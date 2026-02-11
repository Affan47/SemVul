build_src(struct request *rq)
{
char			*url = NULL, *host, *path;
int			urllen;
u_short			port=80;

    if ( !rq || !rq->av_pairs) return(NULL);
    if ( rq->original_host ) {
	host = rq->original_host;
    } else {


        if ( rq->url.host )
                host = rq->url.host;
            else
                host = attr_value(rq->av_pairs, "host");
    }
    if ( !host ) return(NULL);
    if ( rq->original_path ) {
	path = rq->original_path;
    } else
	path = rq->url.path;
    if ( !path ) return(NULL);


    if ( path ) {
	char	*dd;

	urllen = strlen(host)
		+strlen(path) + 20;
	url = malloc(urllen);
	if ( (dd = strchr(host, ':')) ) {
	    u_short host_port;
	    *dd = 0;
	    host_port = (u_short)atoi(dd+1);
	    if ( host_port ) port = host_port;
	} else
	    port = 80;
	if ( url ) {
	    if ( port != 80 )
		sprintf(url, "http://%s:%d%s", host,port,
				path);
	      else
		sprintf(url, "http://%s%s", host,
				path);
	}
	if ( dd ) *dd = ':';
    }
    return(url);
}
