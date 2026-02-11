decode0x0805(const CiffComponent& ciffComponent,
                              const CrwMapping*    ,
                                    Image&         image,
                                    ByteOrder      )
    {
        std::string s(reinterpret_cast<const char*>(ciffComponent.pData()));
        image.setComment(s);
    }
