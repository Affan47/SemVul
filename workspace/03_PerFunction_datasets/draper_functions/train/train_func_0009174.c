ConstNew(
    const std::string & file, unsigned int line,
    const std::string & description,
    const std::string & location)
  {
    ConstPointer      smartPtr;
    const Self *const rawPtr = new Self(file, line, description, location);

    smartPtr = rawPtr;
    rawPtr->LightObject::UnRegister();
    return smartPtr;
  }
