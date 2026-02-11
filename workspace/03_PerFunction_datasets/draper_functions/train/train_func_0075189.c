getCanAnimate() const {
        if (_properties.fetchProperty(kOfxParamPropAnimates))  {
          return _properties.getIntProperty(kOfxParamPropAnimates) != 0;
        }
        return false;
      }
