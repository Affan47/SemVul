neighbour_choose_best_next( ant_struct *a, long int phase )


{
    long int i, current_city, next_city, help_city;
    double   value_best, help;

    next_city = n;
    DEBUG( assert ( phase > 0 && phase < n ); );
    current_city = (*a).tour[phase-1];
    DEBUG ( assert ( 0 <= current_city && current_city < n ); )
    value_best = -1.;
    for ( i = 0 ; i < nn_ants ; i++ ) {
	help_city = instance.nn_list[current_city][i];
	if ( (*a).visited[help_city] )
	    ;
	else {
	    help = total[current_city][help_city];
	    if ( help > value_best ) {
		value_best = help;
		next_city = help_city;
	    }
	}
    }
    if ( next_city == n )

	choose_best_next( a, phase );
    else {
	DEBUG( assert ( 0 <= next_city && next_city < n); )
	DEBUG( assert ( value_best > 0.0 ); )
	DEBUG( assert ( (*a).visited[next_city] == FALSE ); )
	(*a).tour[phase] = next_city;
	(*a).visited[next_city] = TRUE;
    }
}
