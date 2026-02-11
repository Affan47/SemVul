GetLiquidHeight(const Vector3& pos, float& liqHeight) const
    {
        float tx_f = (pos.x - iCorner.x) / LIQUID_TILE_SIZE;
        uint32 tx = uint32(tx_f);
        if (tx_f < 0.0f || tx >= iTilesX)
            return false;
        float ty_f = (pos.y - iCorner.y) / LIQUID_TILE_SIZE;
        uint32 ty = uint32(ty_f);
        if (ty_f < 0.0f || ty >= iTilesY)
            return false;


        if ((iFlags[tx + ty * iTilesX] & 0x0F) == 0x0F)
            return false;


        float dx = tx_f - (float)tx;
        float dy = ty_f - (float)ty;


        const uint32 rowOffset = iTilesX + 1;
        if (dx > dy)
        {
            float sx = iHeight[tx + 1 +  ty    * rowOffset] - iHeight[tx   + ty * rowOffset];
            float sy = iHeight[tx + 1 + (ty + 1) * rowOffset] - iHeight[tx + 1 + ty * rowOffset];
            liqHeight = iHeight[tx + ty * rowOffset] + dx * sx + dy * sy;
        }
        else
        {
            float sx = iHeight[tx + 1 + (ty + 1) * rowOffset] - iHeight[tx + (ty + 1) * rowOffset];
            float sy = iHeight[tx   + (ty + 1) * rowOffset] - iHeight[tx +  ty    * rowOffset];
            liqHeight = iHeight[tx + ty * rowOffset] + dx * sx + dy * sy;
        }
        return true;
    }
