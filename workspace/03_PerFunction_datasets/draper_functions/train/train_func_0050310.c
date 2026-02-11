acceptVisitorGrouped(
        QueuedRenderableVisitor* visitor) const
    {
        PassGroupRenderableMap::const_iterator ipass, ipassend;
        ipassend = mGrouped.end();
        for (ipass = mGrouped.begin(); ipass != ipassend; ++ipass)
        {

            if (ipass->second->empty()) continue;


            if (!visitor->visit(ipass->first))
                continue;

            RenderableList* rendList = ipass->second;
            RenderableList::const_iterator irend, irendend;
            irendend = rendList->end();
            for (irend = rendList->begin(); irend != irendend; ++irend)
            {

                visitor->visit(const_cast<Renderable*>(*irend));
            }
        }

    }
