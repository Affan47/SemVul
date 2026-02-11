getWorldBoundingSphere(bool derive) const
    {
        if (derive)
        {

            ChildObjectList::const_iterator child_itr = mChildObjectList.begin();
            ChildObjectList::const_iterator child_itr_end = mChildObjectList.end();
            for( ; child_itr != child_itr_end; ++child_itr)
            {
                child_itr->second->getWorldBoundingSphere(true);
            }
        }
        return MovableObject::getWorldBoundingSphere(derive);

    }
