move_forward_to(GList* element)
{
    int forward_steps = 0;
    for(GList* itor = const_cast<GList*>(d_forward.list()); itor != NULL; itor = itor->next)
    {
        ++forward_steps;

        if (itor == element)
        {
            for(int i = 0;i < forward_steps;++i)
                move_forward();

            return;
        }
    }

    #ifndef NDEBUG
    cout << "AiksaurusGTK_history::move_forward_to(" << element << ")\n"
         << "Warning: element is not in forward list, and it should be.\n";
    debug();
    #endif
}
