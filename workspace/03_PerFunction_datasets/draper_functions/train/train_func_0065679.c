callEntry(const char *action,
                                      void *handle,
                                      OfxPropertySetHandle inArgs,
                                      OfxPropertySetHandle outArgs)
      {
        if(_entryPoint && _state != eFailed) {
          return _entryPoint(action, handle, inArgs, outArgs);
        }
        else
          return kOfxStatFailed;

        return kOfxStatOK;
      }
