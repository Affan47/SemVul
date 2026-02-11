visitRenderables(Renderable::Visitor* visitor,
        bool debugRenderables)
    {

        for (SubEntityList::iterator i = mSubEntityList.begin(); i != mSubEntityList.end(); ++i)
        {
            visitor->visit(*i, 0, false);
        }
#if !OGRE_NO_MESHLOD

        ushort lodi = 1;
        for (LODEntityList::iterator e = mLodEntityList.begin();
            e != mLodEntityList.end(); ++e, ++lodi)
        {
            if(*e != this) {
                uint nsub = (*e)->getNumSubEntities();
                for (uint s = 0; s < nsub; ++s)
                {
                    visitor->visit((*e)->getSubEntity(s), lodi, false);
                }
            }
        }
#endif
    }
