fillchar_vsep(attr)
    int	    *attr;
{
    *attr = hl_attr(HLF_C);
    if (*attr == 0 && fill_vert == ' ')
	return '|';
    else
	return fill_vert;
}
