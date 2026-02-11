dump_mmp_msg(struct mmp_struct *mmp, const char *msg)
{

	if (msg)
		printf("MMP check failed: %s\n", msg);
	if (mmp) {
		time_t t = mmp->mmp_time;

		printf("MMP error info: last update: %s node: %s device: %s\n",
		       ctime(&t), mmp->mmp_nodename, mmp->mmp_bdevname);
	}
}
