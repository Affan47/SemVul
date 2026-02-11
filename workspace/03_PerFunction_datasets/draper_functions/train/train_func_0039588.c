ReadVal(std::istream &s){
        tString in;
        int keysym;
        s >> keysym;
        if (keysym>=0){
            tASSERT(keysym < SDLK_NEWLAST);
            s >> in;
            if (uBindPlayer::IsKeyWord(in))
            {
                keymap[keysym] = NULL;
                keymap[keysym]=uBindPlayer::NewBind(s);
                if (!keymap[keysym]->act)
                {
                    keymap[keysym]=NULL;
                }


            }
        }
        char c=' ';
        while(c!='\n' && s.good() && !s.eof()) c=s.get();
    }
}
