optContentIsVisible( Object *dictRef )
{
  Object dictObj;
  Dict *dict;
  Object dictType;
  Object ocg;
  Object policy;
  bool result = true;
  dictRef->fetch( m_xref, &dictObj );
  if ( ! dictObj.isDict() ) {
    error(-1, "Unexpected oc reference target: %i", dictObj.getType() );
    dictObj.free();
    return result;
  }
  dict = dictObj.getDict();

  dict->lookup("Type", &dictType);
  if (dictType.isName("OCMD")) {


    dict->lookup("P", &policy);
    dict->lookupNF("OCGs", &ocg);
    if (ocg.isArray()) {
      if (policy.isName("AllOn")) {
	result = allOn( ocg.getArray() );
      } else if (policy.isName("AllOff")) {
	result = allOff( ocg.getArray() );
      } else if (policy.isName("AnyOff")) {
	result = anyOff( ocg.getArray() );
      } else if ( (!policy.isName()) || (policy.isName("AnyOn") ) ) {

	result = anyOn( ocg.getArray() );
      }
    } else if (ocg.isRef()) {
      OptionalContentGroup* oc = findOcgByRef( ocg.getRef() );
      if ( oc && oc->getState() == OptionalContentGroup::Off ) {
	result = false;
      } else {
	result = true ;
      }
    }
    ocg.free();
    policy.free();
  } else if ( dictType.isName("OCG") ) {
    OptionalContentGroup* oc = findOcgByRef( dictRef->getRef() );
    if ( oc && oc->getState() == OptionalContentGroup::Off ) {
      result=false;
    }
  }
  dictType.free();
  dictObj.free();

  return result;
}
