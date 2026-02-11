writeBoneAssignment(TiXmlElement* mBoneAssignNode, const VertexBoneAssignment* assign)
    {
        TiXmlElement* assignNode =
            mBoneAssignNode->InsertEndChild(
            TiXmlElement("vertexboneassignment"))->ToElement();

        assignNode->SetAttribute("vertexindex",
            StringConverter::toString(assign->vertexIndex));
        assignNode->SetAttribute("boneindex",
            StringConverter::toString(assign->boneIndex));
        assignNode->SetAttribute("weight",
            StringConverter::toString(assign->weight));


    }
