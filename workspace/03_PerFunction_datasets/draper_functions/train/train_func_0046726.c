modsout_report_unused_tag( fields *info, int i, param *p, unsigned long numrefs )
{
	if ( p->progname ) fprintf( stderr, "%s: ", p->progname );
	fprintf( stderr, "Ref %lu unused tag: '%s' value: '%s' level: %d\n",
			numrefs+1, info->tag[i].data, info->data[i].data,
			info->level[i] );
}
