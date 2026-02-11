cpp_public_part(std::string &name, std::ofstream &cpp, Arc::XMLNode &xml)
{
    cpp << std::endl;
    cpp << name << "Service::" << name << "Service(Arc::Config *cfg):Service(cfg),logger(Arc::Logger::rootLogger, \"" << name << "\")" << std::endl;
    cpp << "{" << std::endl;
    cpp << "    // Define supported namespaces" << std::endl;
    Arc::NS n = xml.Namespaces();
    Arc::NS::iterator it;
    for (it = n.begin(); it != n.end(); it++) {

        if (it->first != "soap" &&
            it->first != "SOAP-ENV" &&
            it->first != "SOAP-ENC" &&
            it->first != "wsdl" &&
            it->first != "xsd") {
                cpp << "    ns[\"" << it->first << "\"]=\"" << it->second << "\";" << std::endl;
        }
    }
    cpp << "}" << std::endl;
    cpp << std::endl;
    cpp << name << "Service::~" << name << "Service(void)" << std::endl;
    cpp << "{" << std::endl;
    cpp << "}" << std::endl;
    cpp << std::endl;
    cpp << "Arc::MCC_Status " << name << "Service::process(Arc::Message &inmsg, Arc::Message &outmsg)" << std::endl;
    cpp << "{\n\
    // Both input and output are supposed to be SOAP\n\
    // Extracting payload\n\
    Arc::PayloadSOAP* inpayload = NULL;\n\
    try {\n\
      inpayload = dynamic_cast<Arc::PayloadSOAP*>(inmsg.Payload());\n\
    } catch(std::exception& e) { };\n\
    if(!inpayload) {\n\
      logger.msg(Arc::ERROR, \"input is not SOAP\");\n\
      return make_soap_fault(outmsg);\n\
    };\n\
    // Analyzing request\n\
    Arc::XMLNode op = inpayload->Child(0);\n\
    if(!op) {\n\
      logger.msg(Arc::ERROR, \"input does not define operation\");\n\
      return make_soap_fault(outmsg);\n\
    }; \n\
    logger.msg(Arc::VERBOSE,\"process: operation: %s\", op.Name());\n\
    Arc::PayloadSOAP* outpayload = new Arc::PayloadSOAP(ns);\n\
    Arc::PayloadSOAP& res = *outpayload;\n\
    Arc::MCC_Status ret = Arc::STATUS_OK;" << std::endl;

    cpp << "    ";
    Arc::XMLNode op;
    for (int i = 0; (op = xml["wsdl:portType"]["wsdl:operation"][i]) == true; i++) {
        std::string n = (std::string) op.Attribute("name");
        std::string msg = (std::string) op["output"].Attribute("message");
        cpp << "if(MatchXMLName(op, \"" << n << "\")) {" << std::endl;
        cpp << "        Arc::XMLNode r = res.NewChild(\"" << msg << "\");" << std::endl;
        cpp << "        ret = " << n << "(op, r);" << std::endl;
        cpp << "    } else ";
    }
    cpp << "if(MatchXMLName(op, \"DelegateCredentialsInit\")) {\n\
        if(!delegation.DelegateCredentialsInit(*inpayload,*outpayload)) {\n\
          delete inpayload;\n\
          return make_soap_fault(outmsg);\n\
        }\n\
    // WS-Property\n\
    } else if(MatchXMLNamespace(op,\"http://docs.oasis-open.org/wsrf/rp-2\")) {\n\
        Arc::SOAPEnvelope* out_ = infodoc.Process(*inpayload);\n\
        if(out_) {\n\
          *outpayload=*out_;\n\
          delete out_;\n\
        } else {\n\
          delete inpayload; delete outpayload;\n\
          return make_soap_fault(outmsg);\n\
        };\n\
    } else {\n\
        logger.msg(Arc::ERROR,\"SOAP operation is not supported: %s\", op.Name());\n\
        return make_soap_fault(outmsg);\n\
    };\n\
    // Set output\n\
    outmsg.Payload(outpayload);\n\
    return Arc::MCC_Status(ret);\n\
}" << std::endl;

    cpp << std::endl;
}
