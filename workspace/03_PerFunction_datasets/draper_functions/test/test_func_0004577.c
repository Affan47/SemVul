boolReadAttribute(const string& inAttribute)const{
  pair<bool,string> lReadAttribute=stringReadAttribute(inAttribute);

  if(!lReadAttribute.first){
    return make_pair(bool(0),bool(0));
  }else{
    char* lLastCorrectCharacter=0;

    bool lReturnValue=((lReadAttribute.second=="yes")
		       ||
		       (lReadAttribute.second=="y")
		       ||
		       (lReadAttribute.second=="true")
		       ||
		       (lReadAttribute.second=="t"));
    return make_pair(lReadAttribute.first,
		     lReturnValue);
  }
}
