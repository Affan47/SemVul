SetSearchParameter(const Tag& inTag, const std::string& inValue){


    static const Global &g = Global::GetInstance();
    static const Dicts &dicts = g.GetDicts();
    static const Dict &pubdict = dicts.GetPublicDict();

    const DictEntry &dictentry = pubdict.GetDictEntry(inTag);

    SetSearchParameter(inTag, dictentry, inValue);

  }
