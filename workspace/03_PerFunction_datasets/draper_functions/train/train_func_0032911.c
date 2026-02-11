calcAnimationSize(const Skeleton* pSkel, const Animation* pAnim, SkeletonVersion ver)
    {
        size_t size = SSTREAM_OVERHEAD_SIZE;


        size += calcStringSize(pAnim->getName());

        size += sizeof(float);

        if ((int)ver > (int)SKELETON_VERSION_1_0)
        {
            if (pAnim->getUseBaseKeyFrame())
            {
                size += SSTREAM_OVERHEAD_SIZE;

                size += calcStringSize(pAnim->getBaseKeyFrameAnimationName());

                size += sizeof(float);
            }
        }


        Animation::NodeTrackIterator trackIt = pAnim->getNodeTrackIterator();
        while(trackIt.hasMoreElements())
        {
            size += calcAnimationTrackSize(pSkel, trackIt.getNext());
        }

        return size;
    }
