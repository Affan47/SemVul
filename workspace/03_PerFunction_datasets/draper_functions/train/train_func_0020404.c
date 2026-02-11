toXML(bool inIsPrivate)const{
  CXMLHelper lHelper;
  lHelper.setName(mrml_const::algorithm_list);
  string lReturnValue=lHelper.toString()+"\n";

  for(CContent::const_iterator i=mContent.begin();
      i!=mContent.end();
      i++){
    i->second->toXML(lReturnValue);
  }
  lHelper.setEnd();
  lReturnValue+=lHelper.toString()+"\n";
  return lReturnValue;
}
