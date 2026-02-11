_prepareProceduralPage(Page* page, PagedWorldSection* section)
    {
        bool generated = false;
        if (mPageProvider)
            generated = mPageProvider->prepareProceduralPage(page, section);

        return generated;
    }
