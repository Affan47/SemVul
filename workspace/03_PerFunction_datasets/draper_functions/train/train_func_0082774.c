toXML()const{

  char lBuffer[20];
  sprintf(lBuffer,"%lf",mRelevanceLevel);

  return string(string("<sresultelement userrelevance=\"0.5\" "
		       "calculatedsimilarity=\"")+string(lBuffer)+"\" "
		+string("imagelocation=\"")+mURL+string("\"/>\n"));
}
