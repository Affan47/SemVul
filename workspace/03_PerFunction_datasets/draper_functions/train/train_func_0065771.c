DEH_GetChar(deh_context_t *context)
{
    int result = 0;


    do
    {
        switch (context->type)
        {
            case DEH_INPUT_FILE:
                result = DEH_GetCharFile(context);
                break;

            case DEH_INPUT_LUMP:
                result = DEH_GetCharLump(context);
                break;
        }
    } while (result == '\r');


    if (context->last_was_newline)
    {
        ++context->linenum;
    }

    context->last_was_newline = result == '\n';

    return result;
}
