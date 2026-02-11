AcpiDbGetNextToken (
    char                    *String,
    char                    **Next,
    ACPI_OBJECT_TYPE        *ReturnType)
{
    char                    *Start;
    UINT32                  Depth;
    ACPI_OBJECT_TYPE        Type = ACPI_TYPE_INTEGER;


    if (!String || !(*String))
    {
        return (NULL);
    }


    if (*String == ' ')
    {
        while (*String && (*String == ' '))
        {
            String++;
        }

        if (!(*String))
        {
            return (NULL);
        }
    }

    switch (*String)
    {
    case '"':


        String++;
        Start = String;
        Type = ACPI_TYPE_STRING;


        while (*String && (*String != '"'))
        {
            String++;
        }
        break;

    case '(':


        String++;
        Start = String;
        Type = ACPI_TYPE_BUFFER;


        while (*String && (*String != ')'))
        {
            String++;
        }
        break;

    case '[':


        String++;
        Depth = 1;
        Start = String;
        Type = ACPI_TYPE_PACKAGE;


        while (*String)
        {


            if (*String == '"')
            {


                String++;
                while (*String && (*String != '"'))
                {
                    String++;
                }
                if (!(*String))
                {
                    break;
                }
            }
            else if (*String == '[')
            {
                Depth++;
            }
            else if (*String == ']')
            {
                Depth--;
                if (Depth == 0)
                {
                    break;
                }
            }

            String++;
        }
        break;

    default:

        Start = String;


        while (*String && (*String != ' '))
        {
            String++;
        }
        break;
    }

    if (!(*String))
    {
        *Next = NULL;
    }
    else
    {
        *String = 0;
        *Next = String + 1;
    }

    *ReturnType = Type;
    return (Start);
}
