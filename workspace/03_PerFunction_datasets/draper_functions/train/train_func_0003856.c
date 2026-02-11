_addRenderSystemCapabilities(const String& name, RenderSystemCapabilities* caps)
    {
        mCapabilitiesMap.insert(CapabilitiesMap::value_type(name, caps));
    }
