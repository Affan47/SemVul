DtParseLine (
    char                    *LineBuffer,
    UINT32                  Line,
    UINT32                  Offset)
{
    char                    *Start;
    char                    *End;
    char                    *TmpName;
    char                    *TmpValue;
    char                    *Name;
    char                    *Value;
    char                    *Colon;
    UINT32                  Length;
    DT_FIELD                *Field;
    UINT32                  Column;
    UINT32                  NameColumn;
    BOOLEAN                 IsNullString = FALSE;


    if (!LineBuffer)
    {
        return (AE_OK);
    }


    if (strstr (LineBuffer, ACPI_RAW_TABLE_DATA_HEADER))
    {
        return (AE_NOT_FOUND);
    }

    Colon = strchr (LineBuffer, ':');
    if (!Colon)
    {
        return (AE_OK);
    }

    Start = LineBuffer;
    End = Colon;

    while (Start < Colon)
    {
        if (*Start == '[')
        {


            while (Start < Colon && *Start != ']')
            {
                Start++;
            }
        }
        else if (*Start != ' ')
        {
            break;
        }

        Start++;
    }


    Column = ACPI_PTR_DIFF (Colon, LineBuffer) + 3;
    NameColumn = ACPI_PTR_DIFF (Start, LineBuffer) + 1;

    Length = ACPI_PTR_DIFF (End, Start);

    TmpName = UtLocalCalloc (Length + 1);
    ACPI_STRNCPY (TmpName, Start, Length);
    Name = DtTrim (TmpName);
    ACPI_FREE (TmpName);

    Start = End = (Colon + 1);
    while (*End)
    {


        if (*End == '"')
        {
            End++;


            if (*End == '"')
            {
                IsNullString = TRUE;
            }
            while (*End && (*End != '"'))
            {
                End++;
            }

            End++;
            break;
        }


        if (*End == '[')
        {
            End--;
            break;
        }
        End++;
    }

    Length = ACPI_PTR_DIFF (End, Start);
    TmpValue = UtLocalCalloc (Length + 1);

    ACPI_STRNCPY (TmpValue, Start, Length);
    Value = DtTrim (TmpValue);
    ACPI_FREE (TmpValue);


    if ((Value && *Value) || IsNullString)
    {
        Field = UtLocalCalloc (sizeof (DT_FIELD));
        Field->Name = Name;
        Field->Value = Value;
        Field->Line = Line;
        Field->ByteOffset = Offset;
        Field->NameColumn = NameColumn;
        Field->Column = Column;

        DtLinkField (Field);
    }
    else
    {
        ACPI_FREE (Name);
        ACPI_FREE (Value);
    }

    return (AE_OK);
}
