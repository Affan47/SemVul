setFactors(const string& factors)
{
  if (factors.empty()) return;
  vector<string> factors_vec;
  split(factors, '|', factors_vec);
  for(vector<string>::iterator it = factors_vec.begin(); it != factors_vec.end(); ++it)
  {
    int factor = atoi(it->c_str());
    m_factors.push_back(factor);
  }
}
