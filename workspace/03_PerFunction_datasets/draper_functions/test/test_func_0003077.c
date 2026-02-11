preprocess(xs__schema &schema)
{ if (!schemaRef && schemaLocation)
  {
    static map<const char*, xs__schema*, ltstr> included;
    map<const char*, xs__schema*, ltstr>::iterator i = included.end();
    if (schema.targetNamespace)
      for (i = included.begin(); i != included.end(); ++i)
        if ((*i).second->targetNamespace
         && !strcmp(schemaLocation, (*i).first)
         && !strcmp(schema.targetNamespace, (*i).second->targetNamespace))
          break;
    if (i == included.end())
    { if (vflag)
        cerr << "Preprocessing schema include '" << (schemaLocation?schemaLocation:"") << "' into schema '" << (schema.targetNamespace?schema.targetNamespace:"") << "'" << endl;
      included[schemaLocation] = schemaRef = new xs__schema(schema.soap);
      schemaRef->read(schema.sourceLocation(), schemaLocation);
      schemaRef->targetNamespace = schema.targetNamespace;
    }
    else
    { if (vflag)
        cerr << "Schema '" << (schemaLocation?schemaLocation:"") << "' already included into schema '" << (schema.targetNamespace?schema.targetNamespace:"") << "'" << endl;
      schemaRef = (*i).second;
    }
  }
  return SOAP_OK;
}
