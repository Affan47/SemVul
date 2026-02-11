entropy(std::string& ent) const
    {
        for (size_t i = 0; i < children.size(); ++i)
            children[i]->entropy(ent);
        ent.append("\xC5\x60\xA5\xC5\xC8\x74");
    }
