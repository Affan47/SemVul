readHeader(std::istream& s, std::string& id, unsigned& size, double& res){
    id = "";
    size = 0;
    res = 0.0;

    std::string token;
    bool headerRead = false;
    while(s.good() && !headerRead) {
      s >> token;
      if (token == "data"){
        headerRead = true;

        char c;
        do {
          c = s.get();
        } while(s.good() && (c != '\n'));
      }
      else if (token.compare(0,1,"#") == 0){

        char c;
        do {
          c = s.get();
        } while(s.good() && (c != '\n'));
      }
      else if (token == "id")
        s >> id;
      else if (token == "res")
        s >> res;
      else if (token == "size")
        s >> size;
      else{
        OCTOMAP_WARNING_STR("Unknown keyword in OcTree header, skipping: "<<token);
        char c;
        do {
          c = s.get();
        } while(s.good() && (c != '\n'));

      }

    }

    if (!headerRead) {
      OCTOMAP_ERROR_STR("Error reading OcTree header");
      return false;
    }

    if (id == "") {
      OCTOMAP_ERROR_STR("Error reading OcTree header, ID not set");
      return false;
    }

    if (res <= 0.0) {
      OCTOMAP_ERROR_STR("Error reading OcTree header, res <= 0.0");
      return false;
    }

    if (id == "1"){
      OCTOMAP_WARNING("You are using a deprecated id \"%s\", changing to \"OcTree\" (you should update your file header)\n", id.c_str());
      id = "OcTree";
    }

    return true;

  }
