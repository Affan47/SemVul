logInfo( void ) const
    {
        StringStream ssOut( std::stringstream::out );
        ssOut << *this;

        Ogre::LogManager::getSingleton().logMessage( Ogre::LML_NORMAL, ssOut.str()  );
    }
