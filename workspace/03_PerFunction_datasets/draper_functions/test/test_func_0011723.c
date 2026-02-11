make_feature_bag(const int cutoff)
{
  int max_num_features = 0;


#ifdef USE_HASH_MAP
  typedef __gnu_cxx::hash_map<unsigned int, int> map_type;
#else
  typedef std::map<unsigned int, int> map_type;
#endif
  map_type count;
  if (cutoff > 0) {
    for (std::vector<Sample>::const_iterator i = _vs.begin(); i != _vs.end(); i++) {
      for (std::vector<int>::const_iterator j = i->positive_features.begin(); j != i->positive_features.end(); j++) {
        count[ME_Feature(i->label, *j).body()]++;
      }
      for (std::vector<pair<int, double> >::const_iterator j = i->rvfeatures.begin(); j != i->rvfeatures.end(); j++) {
        count[ME_Feature(i->label, j->first).body()]++;
      }
    }
  }

  int n = 0;
  for (std::vector<Sample>::const_iterator i = _vs.begin(); i != _vs.end(); i++, n++) {
    max_num_features = max(max_num_features, (int)(i->positive_features.size()));
    for (std::vector<int>::const_iterator j = i->positive_features.begin(); j != i->positive_features.end(); j++) {
      const ME_Feature feature(i->label, *j);

      if (cutoff > 0 && count[feature.body()] <= cutoff) continue;
      int id = _fb.Put(feature);


    }
    for (std::vector<pair<int, double> >::const_iterator j = i->rvfeatures.begin(); j != i->rvfeatures.end(); j++) {
      const ME_Feature feature(i->label, j->first);

      if (cutoff > 0 && count[feature.body()] <= cutoff) continue;
      int id = _fb.Put(feature);
    }
  }
  count.clear();


  int c = 0;

  init_feature2mef();

  return max_num_features;
}
