get_tree_mirage_num() const
    {
        infinint ret = 0;

        list<nomme *>::const_iterator it = ordered_fils.begin();

        while(it != ordered_fils.end())
        {
            const directory *fils_dir = dynamic_cast<const directory *>(*it);
            const mirage *fils_mir = dynamic_cast<const mirage *>(*it);

            if(fils_mir != NULL)
                ++ret;

            if(fils_dir != NULL)
                ret += fils_dir->get_tree_mirage_num();

            ++it;
        }


        return ret;
    }
