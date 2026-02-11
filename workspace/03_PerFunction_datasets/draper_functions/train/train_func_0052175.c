P_AddMaceSpot(mapthing_t * mthing)
{
    if (MaceSpotCount == MAX_MACE_SPOTS)
    {
        I_Error("Too many mace spots.");
    }
    MaceSpots[MaceSpotCount].x = mthing->x << FRACBITS;
    MaceSpots[MaceSpotCount].y = mthing->y << FRACBITS;
    MaceSpotCount++;
}
