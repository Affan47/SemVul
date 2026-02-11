memoryaddress(int scopebase,string subroutinename,string variablename,
		 map<string,int> &temporal)
{
  if (istemporal(variablename)) {
    return temporal[variablename];
  } else {
    return scopebase+relativeoffset[subroutinename][variablename];
  }
}
