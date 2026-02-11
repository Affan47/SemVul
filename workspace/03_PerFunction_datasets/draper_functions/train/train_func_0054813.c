readBones(Skeleton* skel, TiXmlElement* mBonesNode)
    {
        LogManager::getSingleton().logMessage("XMLSkeletonSerializer: Reading Bones name...");

        Quaternion quat ;

        for (TiXmlElement* bonElem = mBonesNode->FirstChildElement();
            bonElem != 0; bonElem = bonElem->NextSiblingElement())
        {
            String name = bonElem->Attribute("name");
            int id = StringConverter::parseInt(bonElem->Attribute("id"));
            skel->createBone(name,id) ;
        }
    }
