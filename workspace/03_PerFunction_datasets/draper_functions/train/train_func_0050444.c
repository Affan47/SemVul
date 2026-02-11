get_element(Value& aself, const String& aname) {

	if(aname==class_name)
		return this;


	if(aname==class_nametext)
		return new VString(name());


	if(Method* method=get_method(aname))
		return method->get_vjunction(aself);

	return 0;
}
