last_point_over (const double abs, const double thr)
{
  double t = threshold(thr);

  vector<pro_pair >::const_iterator i = v.end();
  i--;
  int counter = v.size();
  while ((*i).abs > abs && i!=v.begin()) {counter --; i--;}

  while ((*i).val < t && counter > lroi && i!=v.begin()) {counter --; i--;};

  if (counter == lroi | i==v.begin()) return -500;
  else
    return (v[counter - 1].abs);
}
