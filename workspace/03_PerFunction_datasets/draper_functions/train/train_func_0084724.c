writeKeyFrame(TiXmlElement* keysNode,
        const TransformKeyFrame* key)
    {
        TiXmlElement* keyNode =
            keysNode->InsertEndChild(TiXmlElement("keyframe"))->ToElement();

        keyNode->SetAttribute("time", StringConverter::toString(key->getTime()));

        TiXmlElement* transNode =
            keyNode->InsertEndChild(TiXmlElement("translate"))->ToElement();
        Vector3 trans = key->getTranslate();
        transNode->SetAttribute("x", StringConverter::toString(trans.x));
        transNode->SetAttribute("y", StringConverter::toString(trans.y));
        transNode->SetAttribute("z", StringConverter::toString(trans.z));

        TiXmlElement* rotNode =
            keyNode->InsertEndChild(TiXmlElement("rotate"))->ToElement();

        Radian angle;
        Vector3 axis;
        key->getRotation().ToAngleAxis(angle, axis);
        TiXmlElement* axisNode =
            rotNode->InsertEndChild(TiXmlElement("axis"))->ToElement();
        rotNode->SetAttribute("angle", StringConverter::toString(angle.valueRadians()));
        axisNode->SetAttribute("x", StringConverter::toString(axis.x));
        axisNode->SetAttribute("y", StringConverter::toString(axis.y));
        axisNode->SetAttribute("z", StringConverter::toString(axis.z));


        if (key->getScale() != Vector3::UNIT_SCALE)
        {
            TiXmlElement* scaleNode =
                keyNode->InsertEndChild(TiXmlElement("scale"))->ToElement();

            scaleNode->SetAttribute("x", StringConverter::toString(key->getScale().x));
            scaleNode->SetAttribute("y", StringConverter::toString(key->getScale().y));
            scaleNode->SetAttribute("z", StringConverter::toString(key->getScale().z));
        }

    }
