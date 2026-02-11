OnDestroy()
    {
        if ( warned_ )
            con << "Flood protection ban of " << GetIP() << " removed because machine is discarded.\n";

        delete this;
    }
