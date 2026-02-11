find_camera_name(int make)
{
    struct camera_name *maker_id;
    char *camera_name = UNKNOWN_CAMERA_STRING;


    for(maker_id = Camera_make; maker_id && maker_id->name; ++maker_id)
    {
        if(make == maker_id->id)
        {
            camera_name = maker_id->name;
            break;
        }
    }
    return(camera_name);
}
