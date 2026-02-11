update_statistics( void )


{

    long int iteration_best_ant;
    double p_x;

    iteration_best_ant = find_best();

    if ( ant[iteration_best_ant].tour_length < (*best_so_far_ant).tour_length ) {

	time_used = elapsed_time( VIRTUAL );
	copy_from_to( &ant[iteration_best_ant], best_so_far_ant );
	copy_from_to( &ant[iteration_best_ant], restart_best_ant );

	found_best = iteration;
	restart_found_best = iteration;
	found_branching = node_branching(lambda);
	branching_factor = found_branching;
	if ( mmas_flag ) {
	    if ( !ls_flag ) {
		p_x = exp(log(0.05)/n);
		trail_min = 1. * (1. - p_x) / (p_x * (double)((nn_ants + 1) / 2));
		trail_max = 1. / ( (rho) * (*best_so_far_ant).tour_length );
		trail_0 = trail_max;
		trail_min = trail_max * trail_min;
	    } else {
		trail_max = 1. / ( (rho) * (*best_so_far_ant).tour_length );
		trail_min = trail_max / ( 2. * n );
		trail_0 = trail_max;
	    }
	}
	write_report();
    }
    if ( ant[iteration_best_ant].tour_length < (*restart_best_ant).tour_length ) {
	copy_from_to( &ant[iteration_best_ant], restart_best_ant );
	restart_found_best = iteration;
	printf("restart best: %ld, restart_found_best %ld, time %.2f\n",(*restart_best_ant).tour_length, restart_found_best, elapsed_time ( VIRTUAL ));
    }
}
