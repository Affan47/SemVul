operator<<(ostream& outStream,
		    const CAccessorElement& inElement){
  outStream << string("CAccessorElement(");
  outStream.operator<<(long(inElement.getID()));
  outStream << string(" ")
	    << inElement.getURL()
	    << string(" ")
	    << inElement.getThumbnailURL()
	    << string(" ")
	    << inElement.getFeatureFileName()
	    << string(")--")
	    << endl;
  return outStream;
}
