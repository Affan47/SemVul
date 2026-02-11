watchForMax(const String& profileName)
    {
        ProfileChildren::iterator it = children.begin(), endit = children.end();
        for(;it != endit; ++it)
        {
            ProfileInstance* child = it->second;
            if( (child->name == profileName && child->watchForMax()) || child->watchForMax(profileName))
                return true;
        }
        return false;
    }
