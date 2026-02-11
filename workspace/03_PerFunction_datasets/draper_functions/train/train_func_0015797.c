get(unsigned index, unsigned int &size,
                        const unsigned char *&data)
{
    size = caches_[index]->getLength();
    data = caches_[index]->getData();
    if (index)
    {
        BlockCache *save = caches_[index];
        unsigned int target = (index >> 1);

        do
        {
            caches_[index] = caches_[index - 1];
            index--;
        }
        while (index > target);
        caches_[target] = save;
    }
}
