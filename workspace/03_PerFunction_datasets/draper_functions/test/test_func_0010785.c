prepare(const String& filename)
    {
        DataStreamPtr stream = ResourceGroupManager::getSingleton().openResource(filename, _getDerivedResourceGroup());

        return prepare(stream);
    }
