executeQuery(Query& query)
{
    QVector <QPair <FilterSearch, int> > filterSearches;
    QVector <QPair <Search*, int> > searches;
    int filterSearchCount = 0;
    int searchCount = 0;
    QTime t;

    t.start();
    m_gamesSearched = 0;

    m_triStateTree = TriStateTree(query);


    int leafNode = 0;
    for(int element = 0; element < query.count(); ++element)
    {
        if(query.isElementSearch(element))
        {
            if(query.search(element)->type() == Search::FilterSearch)
            {
                filterSearches.append(QPair < FilterSearch,
                                      int > (*static_cast < const FilterSearch * >(query.search(element)), leafNode));
            }
            else
            {
                searches.append(QPair < Search*, int >(query.search(element), leafNode));
            }

            ++leafNode;
        }
    }
    filterSearchCount = (int) filterSearches.size();
    searchCount = (int) searches.size();


    for(int searchIndex = 0; searchIndex < size(); ++searchIndex)
    {
        m_triStateTree.clear();


        if(filterSearchCount)
        {
            for(int search = 0; search < filterSearchCount; ++search)
            {
                if(m_triStateTree.setState(filterSearches.at(search).second,
                                           filterSearches.at(search).first.contains(searchIndex)))
                {

                    break;
                }
            }


            if(m_triStateTree.state() == TriStateTree::Unknown)
            {
                for(int search = 0; search < searchCount; ++search)
                {
                    if(m_triStateTree.setState(searches.at(search).second,
                                               searches.at(search).first->matches(searchIndex)))
                    {
                        break;
                    }
                }
                ++m_gamesSearched;
            }
        }
        else
        {


            for(int search = 0; search < searchCount; ++search)
            {
                if(m_triStateTree.setState(searches.at(search).second,
                                           searches.at(search).first->matches(searchIndex)))
                {
                    break;
                }
            }
            ++m_gamesSearched;
        }


        set(searchIndex, m_triStateTree.state() == TriStateTree::True);
    }
    m_searchTime = t.elapsed();

}
