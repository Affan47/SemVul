push()
    {
        template_scope const& old_front = scopes.front();
        scopes.push_front(template_scope());
        scopes.front().parent_1_4 = parent_1_4;
        scopes.front().parent_scope = &old_front;
        parent_1_4 = &scopes.front();
    }
