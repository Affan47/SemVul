tell_master_ready(long long chid)
#else
void
tell_master_ready(chid)
long long chid;
#endif
{
	struct master_command mc;
	bzero(&mc,sizeof(struct master_command));
	if(cdebug>=1)
	{
		fprintf(newstdout,"Child %d: Tell master to go\n",(int)chid);
		fflush(newstdout);
	}
	mc.m_command = R_FLAG_DATA;
	mc.m_mygen = mygen;
	mc.m_version = proto_version;
	mc.m_child_flag = CHILD_STATE_READY;
	mc.m_client_number = (int)chid;
	mc.m_client_error = client_error;
	child_send(controlling_host_name,(struct master_command *)&mc, sizeof(struct master_command));
}
