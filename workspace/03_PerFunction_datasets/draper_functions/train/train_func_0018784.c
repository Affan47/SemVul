LogBins(double xmin, unsigned nbins, double base) {
  vector<double> limits;
  for (unsigned e = 0; e <= nbins; e++)
    limits.push_back(xmin * pow(base, (int)e));
  return limits;
}
