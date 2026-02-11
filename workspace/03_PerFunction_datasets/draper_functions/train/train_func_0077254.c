buildInterpolationSplines(void) const
    {

        if (!mSplines)
        {
            mSplines = OGRE_NEW_T(Splines, MEMCATEGORY_ANIMATION);
        }


        Splines* splines = mSplines;


        splines->positionSpline.setAutoCalculate(false);
        splines->rotationSpline.setAutoCalculate(false);
        splines->scaleSpline.setAutoCalculate(false);

        splines->positionSpline.clear();
        splines->rotationSpline.clear();
        splines->scaleSpline.clear();

        KeyFrameList::const_iterator i, iend;
        iend = mKeyFrames.end();
        for (i = mKeyFrames.begin(); i != iend; ++i)
        {
            TransformKeyFrame* kf = static_cast<TransformKeyFrame*>(*i);
            splines->positionSpline.addPoint(kf->getTranslate());
            splines->rotationSpline.addPoint(kf->getRotation());
            splines->scaleSpline.addPoint(kf->getScale());
        }

        splines->positionSpline.recalcTangents();
        splines->rotationSpline.recalcTangents();
        splines->scaleSpline.recalcTangents();


        mSplineBuildNeeded = false;
    }
