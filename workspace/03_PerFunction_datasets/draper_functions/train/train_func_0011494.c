read(Plane* plane, size_t count)
    {
        for (size_t i = 0; i < count; ++i, ++plane)
        {
            read(&plane->normal);
            read(&plane->d);
        }
    }
