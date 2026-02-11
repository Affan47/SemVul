updateEnemys( int dT ) {
  vector<Formation *>::iterator f;
  for (f = formations.begin(); f != formations.end(); ++f) {
    (*f)->update( dT );
  }
  vector<Enemy *>::iterator i;
  for (i = enemys.begin(); i != enemys.end(); ++i) {
    (*i)->update( dT );
  }
}
