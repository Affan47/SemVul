getOutputListFromString(const string& outList,  const nor_utils::Args* args)
    {
        _outputList.clear();
        for (int i = 0; i < outList.size(); i+=3)
        {
            BaseOutputInfoType* t = BaseOutputInfoType::createOutput(outList.substr(i, 3), args);
            if ( t )  _outputList.push_back(t);
        }

        if ( _outputList.size() == 0 )
            _outputList.push_back(BaseOutputInfoType::createOutput(defaultOutput));


    }
