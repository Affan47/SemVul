sp_get_result(int port,int flag)
#else
void
sp_get_result(port,flag)
int port,flag;
#endif
{
	int tcfd;
	float throughput;
	int count;
	char mybuf[1024];
	int sp_offset,xx;

	tcfd=sp_start_master_listen(port, 1024);
	sp_offset=0;
	while(sp_offset < 1024)
	{
		xx=read(tcfd,&mybuf[sp_offset],1024);
		sp_offset+=xx;
	}
	sscanf(mybuf,"%d %f",&count,&throughput);
	if(!flag)
		printf("%-20s received  %10d Kbytes @ %10.2f Kbytes/sec \n",
			sp_remote_host,count,throughput);
	else
		printf("%-20s  sent     %10d Kbytes @ %10.2f Kbytes/sec \n",
			sp_remote_host,count,throughput);
	close(tcfd);
}
