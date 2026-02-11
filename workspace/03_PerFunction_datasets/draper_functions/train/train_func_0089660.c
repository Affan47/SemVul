createControlParameter (const std::string & variableName,
						  double defStartingValue,
						  double startingValueMin,
						  double startingValueMax) {

  Parameter *par = new Parameter(variableName, defStartingValue, startingValueMin, startingValueMax);
  _data->_controlParameter.push_back(par);
  _data->_controlParameterCache.push_back(defStartingValue);
  return par;

}
