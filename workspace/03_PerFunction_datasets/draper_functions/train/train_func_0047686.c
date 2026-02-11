_parseColourValue(StringVector& vecparams)
    {
        return ColourValue(
            StringConverter::parseReal(vecparams[0]) ,
            StringConverter::parseReal(vecparams[1]) ,
            StringConverter::parseReal(vecparams[2]) ,
            (vecparams.size()==4) ? StringConverter::parseReal(vecparams[3]) : 1.0f ) ;
    }
