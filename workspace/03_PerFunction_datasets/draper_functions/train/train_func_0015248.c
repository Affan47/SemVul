ToXML() const {
    return XMLNode("<jobId>"
                    "<id>"+id+"</id>"
                    "<creamURL>"+creamURL+"</creamURL>"+
                    (!ISB.empty() ? "<property><name>CREAMInputSandboxURI</name><value>" + ISB +"</value></property>" : std::string()) +
                    (!OSB.empty() ? "<property><name>CREAMOutputSandboxURI</name><value>" + OSB +"</value></property>" : std::string()) +
                    "<delegationID>"+delegationID+"</delegationID>"
                   "</jobId>");
  }
