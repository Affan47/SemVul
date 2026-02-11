prepare_cmd_lib(comedi_t *dev, int subdevice, int n_scan, int n_chan, unsigned scan_period_nanosec, comedi_cmd *cmd)
{
	int ret;

	memset(cmd,0,sizeof(*cmd));


	ret = comedi_get_cmd_generic_timed(dev, subdevice, cmd, n_chan, scan_period_nanosec);
	if(ret<0){
		printf("comedi_get_cmd_generic_timed failed\n");
		return ret;
	}


	cmd->chanlist = chanlist;
	cmd->chanlist_len = n_chan;
	if(cmd->stop_src == TRIG_COUNT) cmd->stop_arg = n_scan;

	return 0;
}
