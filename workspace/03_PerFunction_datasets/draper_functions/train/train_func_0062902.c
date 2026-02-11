_updateRenderQueue(RenderQueue* queue)
    {
        if (mVisible)
        {

            if (!mTransparent && !mMaterial.isNull())
            {
                OverlayElement::_updateRenderQueue(queue);
            }


            ChildIterator it = getChildIterator();
            while (it.hasMoreElements())
            {

                it.getNext()->_updateRenderQueue(queue);
            }
        }
    }
