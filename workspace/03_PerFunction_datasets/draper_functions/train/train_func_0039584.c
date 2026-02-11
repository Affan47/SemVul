clipInstanceChangedAction(const std::string & clipName,
                                                    const std::string & why,
                                                    OfxTime     time,
                                                    OfxPointD   renderScale)
      {
        _clipPrefsDirty = true;
        std::map<std::string,ClipInstance*>::iterator it=_clips.find(clipName);
        if(it!=_clips.end())
          return (it->second)->instanceChangedAction(why,time,renderScale);
        else
          return kOfxStatFailed;
      }
