classHandler(Node *n){
    if(!ClassMemberTable)
      ClassMemberTable = NewHash();

    class_name = Getattr(n, "name");
    int status = Language::classHandler(n);

    class_name = NULL;
    return status;
  }
