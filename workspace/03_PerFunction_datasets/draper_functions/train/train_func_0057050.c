hasNonZeroKeyFrames(void) const
    {
        KeyFrameList::const_iterator i = mKeyFrames.begin();
        for (; i != mKeyFrames.end(); ++i)
        {


            TransformKeyFrame* kf = static_cast<TransformKeyFrame*>(*i);
            Vector3 trans = kf->getTranslate();
            Vector3 scale = kf->getScale();
            Vector3 axis;
            Radian angle;
            kf->getRotation().ToAngleAxis(angle, axis);
            Real tolerance = 1e-3f;
            if (!trans.positionEquals(Vector3::ZERO, tolerance) ||
                !scale.positionEquals(Vector3::UNIT_SCALE, tolerance) ||
                !Math::RealEqual(angle.valueRadians(), 0.0f, tolerance))
            {
                return true;
            }

        }

        return false;
    }
