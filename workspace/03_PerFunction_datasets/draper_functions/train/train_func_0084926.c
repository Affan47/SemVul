fractal(const P& p, const P& q, const int depth, const int *pre_seed)
  {
    int spokes(pre_seed[0]);
    int seed_length(pre_seed[1]);
    std::vector<int> seed(seed_length);


    for (int i=0; i<seed_length; ++i)
      seed.at(i) = pre_seed[i+2];


    P scale(jump(spokes, seed_length, seed));


    int length(1+(int)pow(seed_length, depth));
    std::vector<int> dir(length);
    std::vector<P> data(length);


    for(int i=0; i<seed_length; ++i)
      dir.at(i) = seed.at(i);

    for(int i=1; i<depth; ++i)
      for(int j=0; j < pow(seed_length,i); ++j)
	for(int k=seed_length-1; 0 < k; --k)
	  dir.at(k*(int)pow(seed_length,i) + j) = dir.at(j) + seed.at(k);

    P curr(p);

    double radius(pow(norm(scale), 1-depth));

    for(int i=0; i<length; ++i)
      {
	data.at(i) = curr;

	pair temp((polar(radius, dir.at(i)*(full_turn())/spokes))*pair(q-p));


	temp /= pair(scale);

	curr += P(temp.x1(), temp.x2());
      }

    path fractal(data, false, false);
    fractal.draw();
  }
