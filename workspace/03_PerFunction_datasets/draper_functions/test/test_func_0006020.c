obtainlabelname(int scopebase,string subroutinename,string variablename,
	   map<string,int> &temporal)
{
  if (label[subroutinename].find(variablename)!=label[subroutinename].end()) {
    return variablename;
  } else {
    return inttolabelname[value(scopebase,subroutinename,variablename,temporal)];
  }
}
