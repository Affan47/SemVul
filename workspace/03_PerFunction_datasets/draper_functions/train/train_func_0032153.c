readFromFile(FILE* rf, ModelSpawn& spawn)
    {
        uint32 check = 0, nameLen;
        check += fread(&spawn.flags, sizeof(uint32), 1, rf);

        if (!check)
        {
            if (ferror(rf))
                ERROR_LOG("Error reading ModelSpawn!");
            return false;
        }
        check += fread(&spawn.adtId, sizeof(uint16), 1, rf);
        check += fread(&spawn.ID, sizeof(uint32), 1, rf);
        check += fread(&spawn.iPos, sizeof(float), 3, rf);
        check += fread(&spawn.iRot, sizeof(float), 3, rf);
        check += fread(&spawn.iScale, sizeof(float), 1, rf);
        bool has_bound = (spawn.flags & MOD_HAS_BOUND);
        if (has_bound)
        {
            Vector3 bLow, bHigh;
            check += fread(&bLow, sizeof(float), 3, rf);
            check += fread(&bHigh, sizeof(float), 3, rf);
            spawn.iBound = G3D::AABox(bLow, bHigh);
        }
        check += fread(&nameLen, sizeof(uint32), 1, rf);
        if (check != uint32(has_bound ? 17 : 11))
        {
            ERROR_LOG("Error reading ModelSpawn!");
            return false;
        }
        char nameBuff[500];
        if (nameLen > 500)
        {
            ERROR_LOG("Error reading ModelSpawn, file name too long!");
            return false;
        }
        check = fread(nameBuff, sizeof(char), nameLen, rf);
        if (check != nameLen)
        {
            ERROR_LOG("Error reading name string of ModelSpawn!");
            return false;
        }
        spawn.name = std::string(nameBuff, nameLen);
        return true;
    }
