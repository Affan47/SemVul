parseElementAttrib( const String& line, Overlay* pOverlay, OverlayElement* pElement )
    {

        vector<String>::type vecparams = StringUtil::split(line, "\t ", 1);


        StringUtil::toLowerCase(vecparams[0]);
        if (!pElement->setParameter(vecparams[0], vecparams[1]))
        {

            LogManager::getSingleton().logMessage("Bad element attribute line: '"
                + line + "' for element " + pElement->getName() + " in overlay " +
                (!pOverlay ? BLANKSTRING : pOverlay->getName()), LML_CRITICAL);
        }
    }
