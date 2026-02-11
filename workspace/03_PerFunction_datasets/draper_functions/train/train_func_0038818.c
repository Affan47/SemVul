eventKeyDown(const SDL_KeyboardEvent* key) {

        if ( key->keysym.sym == SDLK_RETURN   )
            return ok();

        if ( key->keysym.sym == SDLK_ESCAPE   ) {
            QuitModal();
            return true;
        }

        if ( key->keysym.sym == 'a' ) {
            for ( vector<PG_ListBoxItem*>::const_iterator i = items.begin(); i != items.end(); ++i )
                (*i)->Select( true );
            listbox->Update();
            return true;
        }

        if ( key->keysym.sym == 'n' ) {
            for ( vector<PG_ListBoxItem*>::const_iterator i = items.begin(); i != items.end(); ++i )
                (*i)->Select( false );

            listbox->Update();
            return true;
        }

        return false;
    }
}
