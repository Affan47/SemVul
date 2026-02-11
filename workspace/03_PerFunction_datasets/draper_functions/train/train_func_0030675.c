traverse(wsdl__definitions& definitions)
{ if (vflag)
    cerr << "    Analyzing soap headerfault in wsdl namespace '" << (definitions.targetNamespace?definitions.targetNamespace:"") << "'" << endl;
  messageRef = NULL;
  partRef = NULL;
  const char *token = qname_token(message, definitions.targetNamespace);
  if (token)
  { for (vector<wsdl__message>::iterator message = definitions.message.begin(); message != definitions.message.end(); ++message)
    { if ((*message).name && !strcmp((*message).name, token))
      { messageRef = &(*message);
        if (vflag)
	  cerr << "     Found soap headerfault part '" << (part?part:"") << "' message '" << (token?token:"") << "'" << endl;
        break;
      }
    }
  }
  else
  { for (vector<wsdl__import>::iterator import = definitions.import.begin(); import != definitions.import.end(); ++import)
    { wsdl__definitions *importdefinitions = (*import).definitionsPtr();
      if (importdefinitions)
      { token = qname_token(message, importdefinitions->targetNamespace);
        if (token)
        { for (vector<wsdl__message>::iterator message = importdefinitions->message.begin(); message != importdefinitions->message.end(); ++message)
          { if ((*message).name && !strcmp((*message).name, token))
            { messageRef = &(*message);
              if (vflag)
	        cerr << "     Found soap headerfault part '" << (part?part:"") << "' message '" << (token?token:"") << "'" << endl;
              break;
            }
          }
	}
      }
    }
  }
  if (messageRef)
  { if (part)
    { for (vector<wsdl__part>::iterator pt = messageRef->part.begin(); pt != messageRef->part.end(); ++pt)
        if ((*pt).name && !strcmp((*pt).name, part))
	{ partRef = &(*pt);
	  break;
        }
    }
    if (!partRef)
      cerr << "Warning: soap headerfault has no matching part in message '" << (message?message:"") << "' in wsdl definitions '" << definitions.name << "' namespace '" << (definitions.targetNamespace?definitions.targetNamespace:"") << "'" << endl;
  }
  else
    cerr << "Warning: could not find soap headerfault part '" << (part?part:"") << "' message '" << (message?message:"") << "' in wSDL definitions '" << definitions.name << "' namespace '" << (definitions.targetNamespace?definitions.targetNamespace:"") << "'" << endl;
  return SOAP_OK;
}
