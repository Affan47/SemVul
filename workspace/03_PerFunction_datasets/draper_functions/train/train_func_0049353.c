showProperty( CMPIData data, char *name )
{
	 char *valuestr;
    CMPIValueState state = data.state & ~CMPI_keyValue;
    if (state == CMPI_goodValue)
    {
        if (CMIsArray(data))
        {
	     CMPIArray *arr   = data.value.array;
	     CMPIType  eletyp = data.type & ~CMPI_ARRAY;
	     int j, n;
	     n = CMGetArrayCount(arr, NULL);
            for (j = 0; j < n; ++j)
            {
		CMPIData ele = CMGetArrayElementAt(arr, j, NULL);
		valuestr = value2Chars(eletyp, &ele.value);
	        printf("\t%s[%d]=%s\n", name, j, valuestr);
		free (valuestr);
	     }
        }
        else
        {
            if (state == CMPI_goodValue)
            {
	     valuestr = value2Chars(data.type, &data.value);
	     printf("\t%s=%s\n", name, valuestr);
	     free (valuestr);
	 }
}
    }
    else
    {
        printf("\t%s=%d(%s)\n", name, data.state, CMPIState_str(data.state));
    }
}
