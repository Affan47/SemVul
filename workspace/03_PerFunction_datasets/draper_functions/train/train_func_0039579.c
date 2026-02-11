huawei_read_flowreport(const char *cmd)
{
    char *buf;
    static unsigned long long int prev_tx_flow = 0, prev_rx_flow = 0;
    static unsigned long int prev_ds_time = 0;

    buf = huawei_send_receive(cmd);

    if (strncmp(buf, "^DSFLOWQRY:", 11) == 0) {


	if (sscanf(buf + 11, "%lX,%LX,%LX,%lX,%LX,%LX", &last_ds_time, &last_tx_flow, &last_rx_flow, &total_ds_time,
		   &total_tx_flow, &total_rx_flow) != 6)
	    error("%s: ERROR: Cannot parse all ^DSFLOWQRY: data fields, some data may be wrong or missing", name);


	if (last_ds_time >= prev_ds_time + 2 && last_tx_flow > prev_tx_flow)
	    calc_tx_rate = ((double) (last_tx_flow - prev_tx_flow)) / ((double) (last_ds_time - prev_ds_time));
	else if (last_ds_time >= prev_ds_time + 2 && last_tx_flow == prev_tx_flow)
	    calc_tx_rate = 0;


	if (last_ds_time >= prev_ds_time + 2 && last_rx_flow > prev_rx_flow)
	    calc_rx_rate = ((double) (last_rx_flow - prev_rx_flow)) / ((double) (last_ds_time - prev_ds_time));
	else if (last_ds_time >= prev_ds_time + 2 && last_rx_flow == prev_rx_flow)
	    calc_rx_rate = 0;


	prev_tx_flow = last_tx_flow;
	prev_rx_flow = last_rx_flow;
	prev_ds_time = last_ds_time;

	if (debug) {
	    debug("DEBUG: Last DS connection time [s]: %lu", last_ds_time);
	    debug("DEBUG: Last DS transmiting traffic [bytes]: %llu", last_tx_flow);
	    debug("DEBUG: Last DS receiving traffic [bytes]: %llu", last_rx_flow);
	    debug("DEBUG: Total DS connection time [s]: %lu", total_ds_time);
	    debug("DEBUG: Total DS transmiting trafic [bytes]: %llu", total_tx_flow);
	    debug("DEBUG: Total DS receiving trafic [bytes]: %llu", total_rx_flow);
	    debug("DEBUG: Calculated tx rate [bytes/s]: %lf", calc_tx_rate);
	    debug("DEBUG: Calculated rx rate [bytes/s]: %lf", calc_rx_rate);
	}

    } else
	error("%s: ERROR: Invalid or empty response: \'%s\' received for: \'%s\'", name, buf, cmd);

    return;
}
