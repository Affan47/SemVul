P_DialogGetStates(mobjtype_t type)
{
    int i;


    for(i = 0; i < numdialogstatesets; i++)
    {
        if(type == dialogstatesets[i].type)
            return &dialogstatesets[i];
    }


    return &dialogstatesets[0];
}
