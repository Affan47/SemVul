readAnimations(Skeleton* skel, TiXmlElement* mAnimNode) {

        Animation * anim ;
        NodeAnimationTrack * track ;
        LogManager::getSingleton().logMessage("XMLSkeletonSerializer: Reading Animations data...");

        for (TiXmlElement* animElem = mAnimNode->FirstChildElement("animation"); animElem != 0; animElem = animElem->NextSiblingElement())
        {
            String name = animElem->Attribute("name");
            Real length = StringConverter::parseReal(animElem->Attribute("length"));
            anim = skel->createAnimation(name,length);
            anim->setInterpolationMode(Animation::IM_LINEAR) ;


            TiXmlElement* baseInfoNode = animElem->FirstChildElement("baseinfo");
            if (baseInfoNode)
            {
                String baseName = baseInfoNode->Attribute("baseanimationname");
                Real baseTime = StringConverter::parseReal(baseInfoNode->Attribute("basekeyframetime"));
                anim->setUseBaseKeyFrame(true, baseTime, baseName);
            }


            int trackIndex = 0;
            TiXmlElement* tracksNode = animElem->FirstChildElement("tracks");

            for (TiXmlElement* trackElem = tracksNode->FirstChildElement("track"); trackElem != 0; trackElem = trackElem->NextSiblingElement())
            {
                String boneName = trackElem->Attribute("bone");


                track = anim->createNodeTrack(trackIndex++,skel->getBone(boneName));
                readKeyFrames(track, trackElem->FirstChildElement("keyframes"));
            }

        }


    }
