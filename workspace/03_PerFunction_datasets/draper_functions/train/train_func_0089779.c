do_speed_check(int client_flag)
#else
void
do_speed_check(client_flag)
int client_flag;
#endif
{
	int i;
	if(client_flag)
	{
		speed_main(" "," ",reclen,kilobytes64,client_flag);
	}
	else
	{
		printf("Checking %d clients\n",clients_found);
		for(i=0;i<clients_found;i++)
		{
			speed_main(child_idents[i].child_name,
				child_idents[i].execute_path,
				reclen, kilobytes64,client_flag);
		}
	}
}
