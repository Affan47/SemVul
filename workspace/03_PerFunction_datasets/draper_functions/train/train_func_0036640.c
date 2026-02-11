operator()(const CWeightingFunction& inWF,
			     const CDocumentFrequencyElement& inDFE){
  double lAdjustValue=inWF.apply(inDFE);


    {

    if(find(inDFE.getID())!=end()){

      (*this)[inDFE.getID()] += lAdjustValue;
    }else{

      if (mIgnoreNewValues==false)
	{
	  insert(make_pair
		 (inDFE.getID(),
		  lAdjustValue));
	}
    }
  }
}
