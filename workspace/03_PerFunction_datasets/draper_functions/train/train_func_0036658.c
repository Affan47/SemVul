sgl_column_output_nonformat( struct sgl_column_stats s, char *x )
{
    fprintf( print_out, "%s%s\t%f\n", "mean",   x, s.mean );
    fprintf( print_out, "%s%s\t%f\n", "stddev", x, s.stddev );
    fprintf( print_out, "%s%s\t%f\n", "sum",   x, s.sum );
    fprintf( print_out, "%s%s\t%f\n", "sum_sq",  x, s.sum_sq );

    fprintf( print_out, "%s%s\t%f\n", "min",     x, s.min.val );
    if ( s.sx == 0 ) {
	fprintf( print_out, "%s%s\t%f\n", "lo_quartile", x, s.lower_quartile );
	fprintf( print_out, "%s%s\t%f\n", "median",      x, s.median );
	fprintf( print_out, "%s%s\t%f\n", "up_quartile", x, s.upper_quartile );
    }
    fprintf( print_out, "%s%s\t%f\n", "max",     x, s.max.val );


    if ( s.sx > 0 ) {
	fprintf( print_out, "%s%s\t%ld\n","index_min_x",  x, (s.min.index) / s.sx );
	fprintf( print_out, "%s%s\t%ld\n","index_min_y",  x, (s.min.index) % s.sx );
	fprintf( print_out, "%s%s\t%ld\n","index_max_x",  x, (s.max.index) / s.sx );
	fprintf( print_out, "%s%s\t%ld\n","index_max_y",  x, (s.max.index) % s.sx );
	fprintf( print_out, "%s%s\t%f\n","cog_x",  x, s.cog_x );
	fprintf( print_out, "%s%s\t%f\n","cog_y",  x, s.cog_y );
    } else {
	fprintf( print_out, "%s%s\t%ld\n","min_index",  x, s.min.index );
	fprintf( print_out, "%s%s\t%ld\n","max_index",  x, s.max.index );
    }
}
