writeLog(string &msg_in, string &msg_out)
{
	time_t current_time;
	time (&current_time);
	if (fprintf(fp_log, "Time: %sUser Say: %s\nBot Say: %s\n\n",
		ctime (&current_time), msg_in.c_str(), msg_out.c_str()) == -1)
	{
		fprintf (stderr, "Writing logs to \"chat.log\" error!\n");
		return false;
	}
	else
		return true;

}
