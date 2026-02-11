WriteXML()
{

  std::string logXML = this->LogDir;
  logXML += this->IsError()? "error-" : "warning-";
  logXML += this->LogHash;
  logXML += ".xml";


  cmGeneratedFileStream fxml(logXML.c_str());
  fxml << "\t<Failure type=\""
       << (this->IsError()? "Error" : "Warning") << "\">\n";
  this->WriteXMLAction(fxml);
  this->WriteXMLCommand(fxml);
  this->WriteXMLResult(fxml);
  this->WriteXMLLabels(fxml);
  fxml << "\t</Failure>\n";
}
