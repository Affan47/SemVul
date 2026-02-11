ValidFormatReplacement(char *original, char *replacement)
{
    char *rover1;
    char *rover2;
    int argtype1, argtype2;


    rover1 = original; rover2 = replacement;

    for (;;)
    {
        argtype1 = NextFormatArgument(&rover1);
        argtype2 = NextFormatArgument(&rover2);

        if (argtype2 == FORMAT_ARG_INVALID)
        {


            break;
        }
        else if (argtype1 == FORMAT_ARG_INVALID)
        {


            return false;
        }
        else if (!ValidArgumentReplacement(argtype1, argtype2))
        {


            return false;
        }
    }

    return true;
}
