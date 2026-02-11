trace_graph_thresh_return(struct ftrace_graph_ret *trace)
{
	if (tracing_thresh &&
	    (trace->rettime - trace->calltime < tracing_thresh))
		return;
	else
		trace_graph_return(trace);
}
