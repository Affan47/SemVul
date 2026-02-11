getWorldTransforms(Matrix4* xform) const
    {
        if (mTerrain->_getUseVertexCompression())
        {

            *xform = Matrix4::IDENTITY;
            xform->setTrans(mTerrain->getPosition());

        }
        else
        {

            *xform = mNodeWithVertexData->mMovable->_getParentNodeFullTransform();
        }

    }
