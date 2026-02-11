getColorSpace(const char * name) const
    {
        int index = getIndexForColorSpace(name);
        if(index<0 || index >= (int)getImpl()->colorspaces_.size())
        {
            return ColorSpaceRcPtr();
        }

        return getImpl()->colorspaces_[index];
    }
