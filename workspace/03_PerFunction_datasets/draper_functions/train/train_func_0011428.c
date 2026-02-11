readValue (std::istream &s) {

    char children_char;
    s.read((char*) &value, sizeof(value));
    s.read((char*) &color, sizeof(Color));
    s.read((char*)&children_char, sizeof(char));


    std::bitset<8> children ((unsigned long long) children_char);
    for (unsigned int i=0; i<8; i++) {
      if (children[i] == 1){
        createChild(i);
        getChild(i)->readValue(s);
      }
    }
    return s;
  }
