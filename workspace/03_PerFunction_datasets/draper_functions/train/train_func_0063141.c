set_order( int nest, int num_of_vec, int j, int counter, int *new_floor_order,
	   int * pri_flg, int *now_dependence, int *dependence, int *direction_vec )
{
    int k, m;

    new_floor_order[counter] = j;
    pri_flg[j] = -1;
    for( k = 0; k <num_of_vec; k++ ){
	if( now_dependence[k] == 0 ){
	    if( direction_vec[j+k*nest] < 2 ){
		now_dependence[k] = direction_vec[j+k*nest];
	    }else{
		for( m = j+1; m < nest ; m++ ){
		    if( direction_vec[m+k*nest] != 0 ){
			dependence[k] = direction_vec[m+k*nest];
			m = nest;
		    }
		}
		if( m == nest){
		    dependence[k] = 0;
		}
	    }
	}
    }
}
