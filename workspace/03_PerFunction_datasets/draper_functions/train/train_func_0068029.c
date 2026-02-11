logObjectInfo(const String& msg, const GLhandleARB obj)
    {
        String logMessage = msg;

        if (obj > 0)
        {
            GLint infologLength = 0;

            if(glIsProgram(obj))
                glValidateProgram(obj);

            glGetObjectParameterivARB(obj, GL_OBJECT_INFO_LOG_LENGTH_ARB, &infologLength);

            if (infologLength > 0)
            {
                GLint charsWritten  = 0;

                GLcharARB * infoLog = new GLcharARB[infologLength];

                glGetInfoLogARB(obj, infologLength, &charsWritten, infoLog);
                logMessage += String(infoLog);
                LogManager::getSingleton().logMessage(logMessage);

                delete [] infoLog;
            }
        }

        return logMessage;

    }
