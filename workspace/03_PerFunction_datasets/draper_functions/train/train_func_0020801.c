P_RemoveMobj (mobj_t* mobj)
{

    if ((mobj->flags & MF_SPECIAL)
        && !(mobj->flags & MF_DROPPED))
    {
        itemrespawnque[iquehead] = mobj->spawnpoint;
        itemrespawntime[iquehead] = leveltime + 30*TICRATE;


        if(randomparm && iquehead != iquetail)
        {
            short type    = itemrespawnque[iquehead].type;
            short options = itemrespawnque[iquehead].options;


            itemrespawnque[iquehead].type    = itemrespawnque[iquetail].type;
            itemrespawnque[iquehead].options = itemrespawnque[iquetail].options;
            itemrespawnque[iquetail].type    = type;
            itemrespawnque[iquetail].options = options;
        }

        iquehead = (iquehead+1)&(ITEMQUESIZE-1);


        if (iquehead == iquetail)
            iquetail = (iquetail+1)&(ITEMQUESIZE-1);
    }


    P_UnsetThingPosition (mobj);


    S_StopSound (mobj);


    P_RemoveThinker ((thinker_t*)mobj);
}
