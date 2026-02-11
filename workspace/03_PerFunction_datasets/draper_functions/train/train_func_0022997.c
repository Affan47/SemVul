updatePoseReference(ushort poseIndex, Real influence)
    {
        for (PoseRefList::iterator i = mPoseRefs.begin(); i != mPoseRefs.end(); ++i)
        {
            if (i->poseIndex == poseIndex)
            {
                i->influence = influence;
                return;
            }
        }

        addPoseReference(poseIndex, influence);

    }
