saveg_write_mobj_t(mobj_t *str)
{

    saveg_write_thinker_t(&str->thinker);


    SV_WriteLong(str->x);
    SV_WriteLong(str->y);
    SV_WriteLong(str->z);


    SV_WritePtr(str->snext);
    SV_WritePtr(str->sprev);


    SV_WriteLong(str->angle);


    SV_WriteLong(str->sprite);


    SV_WriteLong(str->frame);


    SV_WritePtr(str->bnext);
    SV_WritePtr(str->bprev);


    SV_WritePtr(str->subsector);


    SV_WriteLong(str->floorz);
    SV_WriteLong(str->ceilingz);


    SV_WriteLong(str->radius);
    SV_WriteLong(str->height);


    SV_WriteLong(str->momx);
    SV_WriteLong(str->momy);
    SV_WriteLong(str->momz);


    SV_WriteLong(str->validcount);


    if (str->type > MT_PHOENIXFX_REMOVED)
    {
        SV_WriteLong(str->type - 1);
    }
    else if (str->type == MT_PHOENIXFX_REMOVED)
    {


        SV_WriteLong(MT_PHOENIXFX1);
    }
    else
    {
        SV_WriteLong(str->type);
    }


    SV_WritePtr(str->info);


    SV_WriteLong(str->tics);


    saveg_write_state_ptr(str->state);


    SV_WriteLong(str->damage);


    SV_WriteLong(str->flags);


    SV_WriteLong(str->flags2);


    saveg_write_specialval_t(&str->special1);


    saveg_write_specialval_t(&str->special2);


    SV_WriteLong(str->health);


    SV_WriteLong(str->movedir);


    SV_WriteLong(str->movecount);


    SV_WritePtr(str->target);


    SV_WriteLong(str->reactiontime);


    SV_WriteLong(str->threshold);


    if (str->player != NULL)
    {
        SV_WriteLong(str->player - players + 1);
    }
    else
    {
        SV_WriteLong(0);
    }


    SV_WriteLong(str->lastlook);


    saveg_write_mapthing_t(&str->spawnpoint);
}
