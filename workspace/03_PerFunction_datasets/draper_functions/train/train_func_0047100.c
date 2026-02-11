readBinary(std::istream &s) {

    this->scan = new Pointcloud();
    this->scan->readBinary(s);

    this->pose.readBinary(s);

    s.read((char*)&this->id, sizeof(this->id));

    return s;
  }
