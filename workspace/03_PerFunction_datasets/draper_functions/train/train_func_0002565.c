acdPrettyUnShift(void)
{
    acdPrettyMargin -= acdPrettyIndent;

    if(acdPrettyMargin < 0)
    {
	ajWarn("acdpretty printing indent error - too many left shifts");
	acdPrettyMargin = 0;
    }

    return;
}
