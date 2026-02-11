extremeRaysInequalityIndices(const IntegerVectorList &inequalityList)
{

  if(rankOfMatrix(inequalityList)==inequalityList.size())
    {
      IntegerVectorList ret;
      int m=inequalityList.size();
      for(int i=0;i<m;i++)
	{
	  IntegerVector v(m-1);
	  for(int j=0;j<i;j++)
	    v[j]=j;
	  for(int j=i+1;j<m;j++)
	    v[j-1]=j;
	  ret.push_back(v);
	}
      return ret;
    }


  LpInit();

  return default_->extremeRaysInequalityIndices(inequalityList);
}
