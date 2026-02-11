ReadChemObject(OBConversion* pConv)
    {

      OBReaction* pReact = new OBReaction;
      bool ret=ReadMolecule(pReact,pConv);

      std::string auditMsg = "OpenBabel::Read reaction ";
      std::string description(Description());
      auditMsg += description.substr(0,description.find('\n'));
      obErrorLog.ThrowError(__FUNCTION__,
          auditMsg,
          obAuditMsg);

      if(ret)
        return pConv->AddChemObject(pReact->DoTransformations(pConv->GetOptions(OBConversion::GENOPTIONS),pConv))!=0;
      else
      {
        pConv->AddChemObject(NULL);
        delete pReact;
        pReact=NULL;
        return false;
      }
    }
