getSlaveToParam(std::vector<std::string>& params) const
      {
        int nSlaveParams = _properties.getDimension(kOfxInteractPropSlaveToParam);

        for (int i=0; i<nSlaveParams; i++) {
          std::string param = _properties.getStringProperty(kOfxInteractPropSlaveToParam, i);
          params.push_back(param);
        }
      }
