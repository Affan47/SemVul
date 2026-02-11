_shuffle
  (const PVector q, const PVector aq, unsigned maxtries) const {

  const size_t nclusters = q.size();
  assert (nclusters > 1);
  assert (aq.size() == nclusters);

  int i, j;
  unsigned tries = 0;
  bool octet;

  do {

    i = UseRandom::irnd( nclusters );
    do { j = UseRandom::irnd( nclusters ); } while (i == j);


    octet = isColour8( q.at(i), aq.at(j) ) || isColour8( q.at(j), aq.at(i) ) ;
    tries++;
  } while (octet && tries < maxtries);

  if (octet) i = j = -1;
  return make_pair(i,j);
}
