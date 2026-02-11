writePoses(TiXmlElement* meshNode, const Mesh* m)
    {
        if (m->getPoseCount() == 0)
            return;

        TiXmlElement* posesNode =
            meshNode->InsertEndChild(TiXmlElement("poses"))->ToElement();

        Mesh::ConstPoseIterator poseIt = m->getPoseIterator();
        while (poseIt.hasMoreElements())
        {
            const Pose* pose = poseIt.getNext();
            TiXmlElement* poseNode =
                posesNode->InsertEndChild(TiXmlElement("pose"))->ToElement();
            unsigned short target = pose->getTarget();
            if (target == 0)
            {

                poseNode->SetAttribute("target", "mesh");
            }
            else
            {

                poseNode->SetAttribute("target", "submesh");
                poseNode->SetAttribute("index",
                    StringConverter::toString(target - 1));
            }
            poseNode->SetAttribute("name", pose->getName());

            bool includesNormals = !pose->getNormals().empty();

            Pose::ConstVertexOffsetIterator vit = pose->getVertexOffsetIterator();
            Pose::ConstNormalsIterator nit = pose->getNormalsIterator();
            while (vit.hasMoreElements())
            {
                TiXmlElement* poseOffsetElement = poseNode->InsertEndChild(
                    TiXmlElement("poseoffset"))->ToElement();

                poseOffsetElement->SetAttribute("index",
                    StringConverter::toString(vit.peekNextKey()));

                Vector3 offset = vit.getNext();
                poseOffsetElement->SetAttribute("x", StringConverter::toString(offset.x));
                poseOffsetElement->SetAttribute("y", StringConverter::toString(offset.y));
                poseOffsetElement->SetAttribute("z", StringConverter::toString(offset.z));

                if (includesNormals)
                {
                    Vector3 normal = nit.getNext();
                    poseOffsetElement->SetAttribute("nx", StringConverter::toString(normal.x));
                    poseOffsetElement->SetAttribute("ny", StringConverter::toString(normal.y));
                    poseOffsetElement->SetAttribute("nz", StringConverter::toString(normal.z));
                }


            }

        }

    }
