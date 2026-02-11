serve_gzip_stream (char *arg)
{
    int level;
    bool forced = false;

    level = atoi (arg);

    if (config && level < config->MinCompressionLevel)
    {
	level = config->MinCompressionLevel;
	forced = true;
    }
    if (config && level > config->MaxCompressionLevel)
    {
	level = config->MaxCompressionLevel;
	forced = true;
    }

    if (forced && !quiet
	&& alloc_pending_warning (120 + strlen (program_name)))
	sprintf (pending_warning_text,
"E %s server: Forcing compression level %d (allowed: %d <= z <= %d).",
		 program_name, level, config->MinCompressionLevel,
		 config->MaxCompressionLevel);

    gzip_level = level;


    buf_from_net = compress_buffer_initialize (buf_from_net, 1,
					       0 ,
					       buf_from_net->memory_error);


# ifdef PROXY_SUPPORT
    if (reprocessing) return;
# endif
    buf_to_net = compress_buffer_initialize (buf_to_net, 0, level,
					     buf_to_net->memory_error);
}
