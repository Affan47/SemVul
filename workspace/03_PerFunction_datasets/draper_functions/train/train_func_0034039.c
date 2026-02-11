AcpiDmPredefinedDescription (
    ACPI_PARSE_OBJECT       *Op)
{
#ifdef ACPI_ASL_COMPILER
    const AH_PREDEFINED_NAME    *Info;
    char                        *NameString;
    int                         LastCharIsDigit;
    int                         LastCharsAreHex;


    if (!Op)
    {
        return;
    }


    if (Op->Common.DisasmFlags & ACPI_PARSEOP_PREDEF_CHECKED)
    {
        return;
    }
    Op->Common.DisasmFlags |= ACPI_PARSEOP_PREDEF_CHECKED;


    NameString = ACPI_CAST_PTR (char, &Op->Named.Name);
    if (NameString[0] != '_')
    {
        return;
    }


    LastCharIsDigit =
        (ACPI_IS_DIGIT (NameString[3]));
    LastCharsAreHex =
        (ACPI_IS_XDIGIT (NameString[2]) &&
         ACPI_IS_XDIGIT (NameString[3]));

    switch (NameString[1])
    {
    case 'A':

        if ((NameString[2] == 'C') && (LastCharIsDigit))
        {
            NameString = "_ACx";
        }
        else if ((NameString[2] == 'L') && (LastCharIsDigit))
        {
            NameString = "_ALx";
        }
        break;

    case 'E':

        if ((NameString[2] == 'J') && (LastCharIsDigit))
        {
            NameString = "_EJx";
        }
        else if (LastCharsAreHex)
        {
            NameString = "_Exx";
        }
        break;

    case 'L':

        if (LastCharsAreHex)
        {
            NameString = "_Lxx";
        }
        break;

    case 'Q':

        if (LastCharsAreHex)
        {
            NameString = "_Qxx";
        }
        break;

    case 'T':

        if (NameString[2] == '_')
        {
            NameString = "_T_x";
        }
        break;

    case 'W':

        if (LastCharsAreHex)
        {
            NameString = "_Wxx";
        }
        break;

    default:

        break;
    }


    Info = AcpiAhMatchPredefinedName (NameString);
    if (Info)
    {
        AcpiOsPrintf ("  // %4.4s: %s",
            NameString, ACPI_CAST_PTR (char, Info->Description));
    }

#endif
    return;
}
