add_period(string *p1)
{
  int p1_val = atoi(p1->c_str());
  det_shocks_periods.push_back(make_pair(p1_val, p1_val));
  delete p1;
}
