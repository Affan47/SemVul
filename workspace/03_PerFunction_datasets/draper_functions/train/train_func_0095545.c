getLastBoundIndex(void) const
    {
        return mBindingMap.empty() ? 0 : mBindingMap.rbegin()->first + 1;
    }
