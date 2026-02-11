parseChildren( DataStreamPtr& stream, const String& line,
            Overlay* pOverlay, bool isATemplate, OverlayContainer* parent)
    {
        bool ret = false;
        uint skipParam =0;
        vector<String>::type params = StringUtil::split(line, "\t\n ()");

        if (isATemplate)
        {
            if (params[0] == "template")
            {
                skipParam++;
            }
        }


        if (params[0+skipParam] == "container" || (params[0+skipParam] == "element" && (isATemplate || parent != NULL)) )
        {
            String templateName;
            ret = true;

            if (params.size() > 3+skipParam)
            {
                if (params.size() != 5+skipParam)
                {
                    LogManager::getSingleton().logMessage(
                        "Bad element/container line: '"
                        + line + "' in " + parent->getTypeName()+ " " + parent->getName() +
                        ", expecting ':' templateName", LML_CRITICAL);
                    skipToNextCloseBrace(stream);

                    return ret;
                }
                if (params[3+skipParam] != ":")
                {
                    LogManager::getSingleton().logMessage(
                        "Bad element/container line: '"
                        + line + "' in " + parent->getTypeName()+ " " + parent->getName() +
                        ", expecting ':' for element inheritance", LML_CRITICAL);
                    skipToNextCloseBrace(stream);

                    return ret;
                }

                templateName = params[4+skipParam];
            }

            else if (params.size() != 3+skipParam)
            {
                LogManager::getSingleton().logMessage(
                    "Bad element/container line: '"
                        + line + "' in " + parent->getTypeName()+ " " + parent->getName() +
                    ", expecting 'element type(name)'");
                skipToNextCloseBrace(stream);

                return ret;
            }

            skipToNextOpenBrace(stream);
            parseNewElement(stream, params[1+skipParam], params[2+skipParam], true, pOverlay, isATemplate, templateName, (OverlayContainer*)parent);

        }


        return ret;
    }
