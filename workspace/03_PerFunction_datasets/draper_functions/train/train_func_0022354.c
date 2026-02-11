traverse(wsdl__definitions& definitions)
{ if (vflag)
    cerr << "    Analyzing soap header in wsdl namespace '" << (definitions.targetNamespace?definitions.targetNamespace:"") << "'" << endl;
  elementRef = NULL;

  if (element)
  { if (definitions.types)
    { for (vector<xs__schema*>::iterator schema = definitions.types->xs__schema_.begin(); schema != definitions.types->xs__schema_.end(); ++schema)
      { const char *token = qname_token(element, (*schema)->targetNamespace);
        if (token)
        { for (vector<xs__element>::iterator element = (*schema)->element.begin(); element != (*schema)->element.end(); ++element)
          { if ((*element).name && !strcmp((*element).name, token))
            { elementRef = &(*element);
              if (vflag)
                cerr << "   Found soap header element '" << (token?token:"") << "'" << endl;
              break;
            }
          }
        }
      }
    }
    if (!elementRef)
    { if (is_builtin_qname(element))
        definitions.builtinElement(element);
      else
        if (!Wflag)
          cerr << "Warning: no soap header element '" << element << "' in wsdl definitions '" << (definitions.name?definitions.name:"") << "' namespace '" << (definitions.targetNamespace?definitions.targetNamespace:"") << "'" << endl;
    }
  }
  return SOAP_OK;
}
