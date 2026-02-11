_CP2DChan_cluster_2piMultD () {


  if (_Rparam >= 0.39) {
    _CP2DChan_limited_cluster(min(_Rparam/2,0.3));
  }


  _CP2DChan_cluster_2pi2R ();
}
