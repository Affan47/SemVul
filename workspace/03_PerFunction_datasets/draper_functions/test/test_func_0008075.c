NotifyUpdate()
{
    for (size_t i = 0; i < max_logs; ++i)
    {
        if (slot[i].log)
            slot[i].log->UpdateSettings();
    }
}
