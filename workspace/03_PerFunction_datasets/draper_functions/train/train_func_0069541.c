send_cid_appstatus(hostname, status)
char *hostname;
u_char status;
{
	cid_changeappmsg_it out;

	strcpy(out.app_id, dacmapid);
	out.app_status = status;
	if (status == APP_RUNNING)
	out.elapsed_time = htonl(time((long *)0) - elapsed_time);
	else out.elapsed_time = elapsed_time;

	if (!changeappmsg(hostname, getpwuid(getuid())->pw_name, out))
		printf("Send app status (%u) failure.\n", status);
}
