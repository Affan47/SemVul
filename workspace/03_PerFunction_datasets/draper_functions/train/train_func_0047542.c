A_RaiseMobj(mobj_t * actor)
{
    int done = true;


    if (actor->floorclip > 0)
    {
        switch (actor->type)
        {
            case MT_WRAITHB:
                actor->floorclip -= 2 * FRACUNIT;
                break;
            case MT_THRUSTFLOOR_DOWN:
            case MT_THRUSTFLOOR_UP:
                actor->floorclip -= actor->special2.i * FRACUNIT;
                break;
            default:
                actor->floorclip -= 2 * FRACUNIT;
                break;
        }
        if (actor->floorclip <= 0)
        {
            actor->floorclip = 0;
            done = true;
        }
        else
        {
            done = false;
        }
    }
    return done;
}
