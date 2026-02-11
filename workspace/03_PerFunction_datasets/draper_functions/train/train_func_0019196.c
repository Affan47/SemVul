setWorldGeometry(DataStreamPtr& stream,
        const String& typeName)
    {
        mLevel.setNull();


        mLevel = BspResourceManager::getSingleton().load(stream,
            ResourceGroupManager::getSingleton().getWorldResourceGroupName()).staticCast<BspLevel>();

        if (mLevel->isSkyEnabled())
        {

            Quaternion q;
            q.FromAngleAxis(Radian(Math::HALF_PI), Vector3::UNIT_X);

            setSkyDome(true, mLevel->getSkyMaterialName(),
                mLevel->getSkyCurvature(), 12, 2000, false, q);
        }
        else
        {
            setSkyDome(false, BLANKSTRING);
        }


        mRenderOp.vertexData = mLevel->mVertexData;

        mRenderOp.indexData = OGRE_NEW IndexData();
        mRenderOp.indexData->indexStart = 0;
        mRenderOp.indexData->indexCount = 0;

        mRenderOp.indexData->indexBuffer = HardwareBufferManager::getSingleton()
            .createIndexBuffer(
                HardwareIndexBuffer::IT_32BIT,
                mLevel->mNumIndexes,
                HardwareBuffer::HBU_DYNAMIC_WRITE_ONLY_DISCARDABLE, false);

        mRenderOp.operationType = RenderOperation::OT_TRIANGLE_LIST;
        mRenderOp.useIndexes = true;


    }
