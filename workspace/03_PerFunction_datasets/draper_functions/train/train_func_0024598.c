AddCompileFlags(cmXmlWriter& xmlWriter, cmMakefile& makefile) const {

    string property = makefile.GetProperty("COMPILE_DEFINITIONS");


    vector<string> definitions;
    cmSystemTools::ExpandListArgument(property, definitions);


    stringstream out;
    for (vector<string>::const_iterator it = definitions.begin(); it != definitions.end();) {
      const string& definition = *it;
      out << "-D" << cmXMLSafe(definition);
      it++;
      if (it != definitions.end()) {
        out << " ";
      }
    }

    string buildType = makefile.GetDefinition("CMAKE_BUILD_TYPE");


    xmlWriter.AddTag(XML_TAG_COMMANDLINE, out.str());
  }
