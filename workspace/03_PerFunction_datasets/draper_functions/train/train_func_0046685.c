AddSignatureTemplate(const std::string& id_name, const SignatureMethod sign_method,
  const std::string& incl_namespaces) {
  xmlNodePtr signature = NULL;
  xmlNodePtr reference = NULL;
  if(sign_method == RSA_SHA1)
    signature = xmlSecTmplSignatureCreate(NULL, xmlSecTransformExclC14NId, xmlSecTransformRsaSha1Id, NULL);
  else
    signature = xmlSecTmplSignatureCreate(NULL, xmlSecTransformExclC14NId, xmlSecTransformDsaSha1Id, NULL);


  xmlNodePtr nd = this->node_;
  xmlAddChild(nd, signature);


  xmlDocPtr docPtr = nd->doc;
  xmlChar* id = NULL;
  id =  xmlGetProp(nd, (xmlChar *)(id_name.c_str()));
  if(!id) { std::cerr<<"There is not "<<id_name<<" attribute in xml node"<<std::endl; return; }

  std::string uri; uri.append("#"); uri.append((char*)id);

  reference = xmlSecTmplSignatureAddReference(signature, xmlSecTransformSha1Id,
                                              NULL, (xmlChar *)(uri.c_str()), NULL);
  xmlSecTmplReferenceAddTransform(reference, xmlSecTransformEnvelopedId);
  xmlNodePtr transform = NULL;
  transform = xmlSecTmplReferenceAddTransform(reference, xmlSecTransformExclC14NId);
  if(!incl_namespaces.empty())
    xmlSecTmplTransformAddC14NInclNamespaces(transform, (const xmlChar*)(incl_namespaces.c_str()));

  xmlAttrPtr id_attr = xmlHasProp(nd, (xmlChar *)(id_name.c_str()));
  xmlAddID(NULL, docPtr, (xmlChar *)id, id_attr);
  xmlFree(id);

  xmlNodePtr key_info = xmlSecTmplSignatureEnsureKeyInfo(signature, NULL);
  xmlSecTmplKeyInfoAddX509Data(key_info);
}
