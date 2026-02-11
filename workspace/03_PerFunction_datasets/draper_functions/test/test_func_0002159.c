getLiquidStatus(float x, float y, float z, uint8 ReqLiquidType, GridMapLiquidData* data) const
{
    GridMapLiquidStatus result = LIQUID_MAP_NO_WATER;
    VMAP::IVMapManager* vmgr = VMAP::VMapFactory::createOrGetVMapManager();
    uint32 liquid_type = 0;
    float liquid_level = INVALID_HEIGHT_VALUE;
    float ground_level = GetHeightStatic(x, y, z, true, DEFAULT_WATER_SEARCH);

    if (vmgr->GetLiquidLevel(GetMapId(), x, y, z, ReqLiquidType, liquid_level, ground_level, liquid_type))
    {


        if (liquid_level > ground_level && z > ground_level - 2)
        {

            if (data)
            {
                uint32 liquidFlagType = 0;
                if (LiquidTypeEntry const* liq = sLiquidTypeStore.LookupEntry(liquid_type))
                    { liquidFlagType = 1 << liq->Type; }

                data->level = liquid_level;
                data->depth_level = ground_level;

                data->entry = liquid_type;
                data->type_flags = liquidFlagType;
            }


            int delta = int((liquid_level - z) * 10);


            if (delta > 20)
                { return LIQUID_MAP_UNDER_WATER; }
            if (delta > 0)
                { return LIQUID_MAP_IN_WATER; }
            if (delta > -1)
                { return LIQUID_MAP_WATER_WALK; }
            result = LIQUID_MAP_ABOVE_WATER;
        }
    }
    else if (GridMap* gmap = const_cast<TerrainInfo*>(this)->GetGrid(x, y))
    {
        GridMapLiquidData map_data;
        GridMapLiquidStatus map_result = gmap->getLiquidStatus(x, y, z, ReqLiquidType, &map_data);

        if (map_result != LIQUID_MAP_NO_WATER && (map_data.level > ground_level))
        {
            if (data)
                { *data = map_data; }

            return map_result;
        }
    }
    return result;
}
