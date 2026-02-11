_tenCalcdists(const int centcount, const double centroid[],
              const int gradcount, const double qpoints[], double dists[] ) {
  int i,j;
  for( j = 0; j < centcount; j++ )
    for( i = 0; i < gradcount; i++ )
      dists[j*gradcount +i] = _tenPldist(&qpoints[3*i], &centroid[3*j]);


}
