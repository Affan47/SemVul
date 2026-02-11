traverse(xs__schema &schema)
{ if (vflag)
    cerr << "   Analyzing schema complexType '" << (name?name:"") << "'" << endl;
  schemaRef = &schema;
  if (simpleContent)
    simpleContent->traverse(schema);
  else if (complexContent)
    complexContent->traverse(schema);
  else if (all)
    all->traverse(schema);
  else if (choice)
    choice->traverse(schema);
  else if (sequence)
    sequence->traverse(schema);
  else if (any)
    any->traverse(schema);
  for (vector<xs__attribute>::iterator at = attribute.begin(); at != attribute.end(); ++at)
    (*at).traverse(schema);
  for (vector<xs__attributeGroup>::iterator ag = attributeGroup.begin(); ag != attributeGroup.end(); ++ag)
    (*ag).traverse(schema);
  return SOAP_OK;
}
