evaporation_nn_list( void )


{
    long int    i, j, help_city;

    TRACE ( printf("pheromone evaporation nn_list\n"); );

    for ( i = 0 ; i < n ; i++ ) {
	for ( j = 0 ; j < nn_ants ; j++ ) {
	    help_city = instance.nn_list[i][j];
	    pheromone[i][help_city] = (1 - rho) * pheromone[i][help_city];
	}
    }
}
