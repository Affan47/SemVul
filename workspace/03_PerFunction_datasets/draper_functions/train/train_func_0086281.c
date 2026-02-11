GetValue(const wstring& parameter, double& value) {
    string sParameter(parameter.begin(), parameter.end());
    return GetValue(sParameter, value);
  }
