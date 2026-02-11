clean(int type) {
  for (unsigned int i=0 ; i<links.size() ; i++) {
    if (i%10000000==0) fprintf(stderr,".");fflush(stderr);
    map<int,int> m;
    map<int,int>::iterator it;

    for (unsigned int j=0 ; j<links[i].size() ; j++) {
      it = m.find(links[i][j].first);
      if (it==m.end())
	      m.insert(make_pair(links[i][j].first, links[i][j].second));
      else if (type==WEIGHTED)
      	it->second+=links[i][j].second;
    }

    vector<pair<int,int> > v;
    for (it = m.begin() ; it!=m.end() ; it++)
      v.push_back(*it);
    links[i].clear();
    links[i]=v;
  }
}
