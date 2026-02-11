GetParameterUFF(std::string a, vector<OBFFParameter> &parameter)
  {
    for (unsigned int idx=0; idx < parameter.size(); ++idx) {
      if (a == parameter[idx]._a) {
        return &parameter[idx];
      }
    }
    return NULL;
  }
