Delete()
{
    int i = index;
    *this = se_lines(se_lines.Len()-1);
    index = i;

    if (se_lines.Len() > 0)
        se_lines.SetLen(se_lines.Len()-1);
}
