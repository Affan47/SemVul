notify(const std::string &name, bool single, int num) OFX_EXCEPTION_SPEC
      {
        Instance::notify(name, single, num);
        if (name == kOfxParamPropChoiceOption) {
          setOption(num);
        }
      }
