report_stream (const cl_timing& t)
{
	var const cl_time_consumption usage_end = cl_current_time_consumption();
	var const cl_time_consumption& usage_start = t.tmp;
	var cl_time_consumption usage;
	usage.realtime = usage_end.realtime - usage_start.realtime;
	usage.usertime = usage_end.usertime - usage_start.usertime;

	var std::ostream& destination = *(std::ostream*) t.report_destination;
	if (t.comment)
		fprint(destination,t.comment);
	cl_timing_report(destination,usage);
	fprint(destination,"\n");
}
