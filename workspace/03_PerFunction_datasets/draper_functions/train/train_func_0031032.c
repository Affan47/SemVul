set_ref_dist(Sample & s) const
{
  vector<double> v0 = s.ref_pd;
  vector<double> v(_num_classes);
  for (int i = 0; i < v.size(); i++) {
    v[i] = 0;
    string label = get_class_label(i);
    int id_ref = _ref_modelp->get_class_id(label);
    if (id_ref != -1) {
      v[i] = v0[id_ref];
    }
    if (v[i] == 0) v[i] = 0.001;
  }
  s.ref_pd = v;
}
