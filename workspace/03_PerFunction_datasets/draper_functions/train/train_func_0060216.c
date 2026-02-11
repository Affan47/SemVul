echo_exec ( int argc, char **argv ) {
	struct echo_options opts;
	char *text;
	int rc;


	if ( ( rc = parse_options ( argc, argv, &echo_cmd, &opts ) ) != 0 )
		return rc;


	text = concat_args ( &argv[optind] );
	if ( ! text )
		return -ENOMEM;


	printf ( "%s%s", text, ( opts.no_newline ? "" : "\n" ) );

	free ( text );
	return 0;
}
