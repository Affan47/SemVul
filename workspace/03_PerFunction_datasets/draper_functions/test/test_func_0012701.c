createNewSegment(const String& name) const
    {

        if (d_segmentWidgetType.empty())
        {
            InvalidRequestException("FalagardListHeader::createNewSegment - Segment widget type has not been set!");
        }

        return static_cast<ListHeaderSegment*>(WindowManager::getSingleton().createWindow(d_segmentWidgetType, name));
    }
