readBoneAssignments(TiXmlElement* mBoneAssignmentsNode, SubMesh* sm)
    {
        LogManager::getSingleton().logMessage("Reading bone assignments...");

        for (TiXmlElement* elem = mBoneAssignmentsNode->FirstChildElement();
        elem != 0; elem = elem->NextSiblingElement())
        {
            VertexBoneAssignment vba;
            vba.vertexIndex = StringConverter::parseInt(
                elem->Attribute("vertexindex"));
            vba.boneIndex = StringConverter::parseInt(
                elem->Attribute("boneindex"));
            vba.weight= StringConverter::parseReal(
                elem->Attribute("weight"));

            sm->addBoneAssignment(vba);
        }
        LogManager::getSingleton().logMessage("Bone assignments done.");
    }
