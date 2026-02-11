writeTextureAliases(TiXmlElement* mSubmeshesNode, const SubMesh* subMesh)
    {
        if (!subMesh->hasTextureAliases())
            return;

        TiXmlElement* textureAliasesNode =
            mSubmeshesNode->InsertEndChild(TiXmlElement("textures"))->ToElement();


        SubMesh::AliasTextureIterator aliasIterator = subMesh->getAliasTextureIterator();

        while (aliasIterator.hasMoreElements())
        {
            TiXmlElement* aliasTextureNode =
                textureAliasesNode->InsertEndChild(TiXmlElement("texture"))->ToElement();

            aliasTextureNode->SetAttribute("alias", aliasIterator.peekNextKey());
            aliasTextureNode->SetAttribute("name", aliasIterator.peekNextValue());
            aliasIterator.moveNext();
        }

    }
