dxf_read_float64(DxfGlobalData *global)
{
	if(global->binary)
		return g3d_stream_read_double_le(global->stream);
	else
	{
		gdouble val;
		gchar line[DXF_MAX_LINE];

		g3d_stream_read_line(global->stream, line, DXF_MAX_LINE);
		if(sscanf(line, "%lf", &val) == 1)
			return val;
		if(sscanf(line, " %lf", &val) == 1)
			return val;
		else
			return 0.0;
	}
}
