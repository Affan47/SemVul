logParseError(const String& error, const MaterialScriptContext& context)
    {

        if (context.filename.empty() && !context.material.isNull())
        {
            LogManager::getSingleton().logMessage(
                "Error in material " + context.material->getName() +
                " : " + error, LML_CRITICAL);
        }
        else
        {
            if (!context.material.isNull())
            {
                LogManager::getSingleton().logMessage(
                    "Error in material " + context.material->getName() +
                    " at line " + StringConverter::toString(context.lineNo) +
                    " of " + context.filename + ": " + error, LML_CRITICAL);
            }
            else
            {
                LogManager::getSingleton().logMessage(
                    "Error at line " + StringConverter::toString(context.lineNo) +
                    " of " + context.filename + ": " + error, LML_CRITICAL);
            }
        }
    }
