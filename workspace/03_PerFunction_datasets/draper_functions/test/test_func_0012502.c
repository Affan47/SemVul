Find( char const * name )
{
    for(int i=su_allActionsLen-1;i>=0;i--)
        if(!strcmp(name,su_allActions[i]->internalName))
            return su_allActions[i];

    return 0;
}
