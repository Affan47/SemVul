add(template_symbol const& ts)
    {
        BOOST_ASSERT(!scopes.empty());
        BOOST_ASSERT(ts.lexical_parent);

        if (this->find_top_scope(ts.identifier)) {
            return false;
        }

        boost::spirit::classic::add(scopes.front().symbols,
            ts.identifier.c_str(), ts);

        return true;
    }
