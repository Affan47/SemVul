writeAnimation(const Skeleton* pSkel,
        const Animation* anim, SkeletonVersion ver)
    {
        writeChunkHeader(SKELETON_ANIMATION, calcAnimationSize(pSkel, anim, ver));


        writeString(anim->getName());

        float len = anim->getLength();
        writeFloats(&len, 1);
        pushInnerChunk(mStream);
        {
        if ((int)ver > (int)SKELETON_VERSION_1_0)
        {
            if (anim->getUseBaseKeyFrame())
            {
                size_t size = SSTREAM_OVERHEAD_SIZE;

                    size += calcStringSize(anim->getBaseKeyFrameAnimationName());

                size += sizeof(float);

                writeChunkHeader(SKELETON_ANIMATION_BASEINFO, size);


                writeString(anim->getBaseKeyFrameAnimationName());


                float t = (float)anim->getBaseKeyFrameTime();
                writeFloats(&t, 1);
            }
        }


        Animation::NodeTrackIterator trackIt = anim->getNodeTrackIterator();
        while(trackIt.hasMoreElements())
        {
            writeAnimationTrack(pSkel, trackIt.getNext());
        }
        }
        popInnerChunk(mStream);

    }
