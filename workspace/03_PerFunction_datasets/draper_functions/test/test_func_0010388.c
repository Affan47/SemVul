freePathContents(NewPath* path)
{
    unsigned count;

    for(count = 0; count < path->numChildren; count++)
    {


        if(path->children[count] == NULL)
            break;

        free(path->children[count]);
    }

    if(path->children != NULL)
        free(path->children);
}
