operator()(const char* name,
               const value_semantic* s,
               const char* description)
    {
        shared_ptr<option_description> d(new option_description(name, s, description));

        owner->add(d);
        return *this;
    }
