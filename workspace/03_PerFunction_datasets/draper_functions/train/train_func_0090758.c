ok() {
        for ( int i = 0; i < items.size(); ++i )
            ItemFiltrationSystem::itemFilters[i]->setActive( !items[i]->IsSelected() );

        QuitModal();
        return true;
    }
