sp_send_result(int port, int count, float throughput)
#else
void
sp_send_result(port, count, throughput)
int port,count;
float throughput;
#endif
{
	int msfd;
	char mybuf[1024];
	sprintf(mybuf,"%d %f",count, throughput);
	msfd=sp_start_child_send(sp_dest, port, &sp_my_cs_addr);
	junk=write(msfd,mybuf,1024);
	if(cdebug)
	{
		fprintf(newstdout,"Sending result\n");
		fflush(newstdout);
	}
	close(msfd);
}
