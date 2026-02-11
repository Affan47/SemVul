ea_detach() const
    {
        if(ea != NULL)
        {
            delete ea;
            const_cast<ea_attributs *&>(ea) = NULL;
        }
    }
