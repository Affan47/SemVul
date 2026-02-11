print_camera_models(struct camera_id *model_names,char *pattern)
{
    struct camera_id *maker_id;
    int chpr = 0;

    chpr = newline(0);
    for(maker_id = model_names ; maker_id && maker_id->name; ++maker_id)
    {
        if(pattern)
        {
            if(STRCASESTR(maker_id->name,pattern))
            {
                chpr += printf("\t\t%-32.32s ",maker_id->name);
                chpr += printf("\t[%2d,%d]",maker_id->id,
                                maker_id->noteversion);
                chpr = newline(chpr);
            }
        }
        else
        {
            chpr += printf("\t\t%-32.32s ",maker_id->name);
            chpr += printf("\t[%2d,%d]",maker_id->id,
                                maker_id->noteversion);
            chpr = newline(chpr);
        }
    }
}
