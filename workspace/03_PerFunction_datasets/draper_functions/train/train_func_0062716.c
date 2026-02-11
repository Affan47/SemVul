operator()(Map* map)
    {

        if (map->IsLoaded(i_data->posX, i_data->posY))
        {
            GameObject* pGameobject = new GameObject;

            if (!pGameobject->LoadFromDB(i_guid, map))
            {
                delete pGameobject;
            }
            else
            {
                if (pGameobject->isSpawnedByDefault())
                    { map->Add(pGameobject); }
            }
        }
    }
