s3_get_file(const char* localname, struct s3_dirent_object *dirent, char* remotename, char* bucketname, const char* access_key_id, const char* access_key) {
	struct s3_message mesg;
	struct link* server;
	time_t stoptime = time(0)+s3_timeout;
	char response[HEADER_LINE_MAX];

	int length;
	FILE* outfile;

	if(!access_key_id || !access_key || !s3_endpoint) return -1;

	mesg.type = S3_MESG_GET;
	mesg.path = remotename;
	mesg.bucket = bucketname;
	mesg.content_type = NULL;
	mesg.content_md5 = NULL;
	mesg.content_length = 0;
	mesg.date = time(0);
	mesg.expect = 0;
	mesg.amz_headers = NULL;


	sign_message(&mesg, access_key_id, access_key);
	server = s3_send_message(&mesg, NULL, stoptime);
	if(!server)
		return -1;


	link_readline(server, response, HEADER_LINE_MAX, stoptime);
	if(strcmp(response, "HTTP/1.1 200 OK")) {


		link_close(server);
		return -1;
	}

	do {
		if(!strncmp(response, "Content-Length:", 14)) {
			sscanf(response, "Content-Length: %d", &length);
		} else if(dirent && dirent->metadata && !strncmp(response, "x-amz-meta-", 11)) {
			struct amz_metadata_object *obj;
			obj = malloc(sizeof(*obj));
			sscanf(response, "x-amz-meta-%[^:]: %s", obj->type, obj->value);
			list_push_tail(dirent->metadata, obj);
		} else if(dirent && !strncmp(response, "Last-Modified:", 14)) {
			struct tm date;
			char date_str[1024];
			sscanf(response, "Last-Modified: %s", date_str);
			strptime(date_str, "%a, %d %b %Y %H:%M:%S %Z", &date);
			date.tm_isdst = -1;
			dirent->last_modified = mktime(&date);
		} else if(dirent && !strncmp(response, "ETag:", 5)) {
			sscanf(response, "ETag: \"%[^\"]\"", dirent->digest);
		}

		if(!strcmp(response, "Server: AmazonS3")) break;
	} while(link_readline(server, response, HEADER_LINE_MAX, stoptime));

	if(dirent) {
		dirent->size = length;
		sprintf(dirent->key, "%s", remotename);
	}

	link_readline(server, response, HEADER_LINE_MAX, stoptime);
	outfile = fopen(localname, "w");
	if(!outfile) {

		link_close(server);
		return -1;
	}
	link_stream_to_file(server, outfile, length, stoptime);
	fclose(outfile);

	link_close(server);
	return 0;
}
