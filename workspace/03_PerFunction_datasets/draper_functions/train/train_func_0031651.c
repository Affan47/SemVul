writeSkeletonLink(TiXmlElement* mMeshNode, const String& skelName)
    {

        TiXmlElement* skelNode =
            mMeshNode->InsertEndChild(TiXmlElement("skeletonlink"))->ToElement();
        skelNode->SetAttribute("name", skelName);
    }
