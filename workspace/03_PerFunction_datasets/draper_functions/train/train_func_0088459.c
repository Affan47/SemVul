vl_ikm_push_one (vl_ikmacc_t const *centers,
		 vl_uint8 const *data,
		 vl_size M, vl_size K)
{
  vl_uindex i,k ;


  vl_uindex best = (vl_uindex) -1 ;
  vl_ikmacc_t best_dist = 0 ;

  for(k = 0 ; k < K ; ++k) {
    vl_ikmacc_t dist = 0 ;


    for(i = 0 ; i < M ; ++i) {
      vl_ikmacc_t delta = (vl_ikmacc_t)data[i] - centers[k*M + i] ;
      dist += delta * delta ;
    }


    if (best == (vl_uindex) -1 || dist < best_dist) {
      best = k  ;
      best_dist = dist ;
    }
  }
  return (vl_uint32)best;
}
