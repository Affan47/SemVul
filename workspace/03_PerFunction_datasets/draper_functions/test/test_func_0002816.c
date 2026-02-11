readSkeletonAnimationLinks(Skeleton* skel,
        TiXmlElement* linksNode)
    {
        LogManager::getSingleton().logMessage("XMLSkeletonSerializer: Reading Animations links...");

        for (TiXmlElement* linkElem = linksNode->FirstChildElement("animationlink");
            linkElem != 0; linkElem = linkElem->NextSiblingElement())
        {
            String skelName = linkElem->Attribute("skeletonName");
            const char* strScale = linkElem->Attribute("scale");
            Real scale;

            if (strScale == 0)
            {
                scale = 1.0f;
            }
            else
            {
                scale = StringConverter::parseReal(strScale);
            }
            skel->addLinkedSkeletonAnimationSource(skelName, scale);

        }
    }
