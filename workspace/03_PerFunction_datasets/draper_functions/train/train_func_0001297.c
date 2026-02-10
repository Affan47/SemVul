Roll() const
{
    if (!ExplicitlyChanced.empty())
    {
        float Roll = rand_chance_f();

        for (uint32 i = 0; i < ExplicitlyChanced.size(); ++i)
        {
            if (ExplicitlyChanced[i].chance >= 100.0f)
                { return &ExplicitlyChanced[i]; }

            Roll -= ExplicitlyChanced[i].chance;
            if (Roll < 0)
                { return &ExplicitlyChanced[i]; }
        }
    }
    if (!EqualChanced.empty())
        { return &EqualChanced[irand(0, EqualChanced.size() - 1)]; }

    return NULL;
}
