name_for_color_idx(unsigned char idx)
{
    size_t max = sizeof named_colors / sizeof *named_colors;
    for (size_t i=0; i < max; i++)
    {
        if (named_colors[i].idx == idx)
        {
            return named_colors[i].name;
        }
    }
    return L"unknown";
}
