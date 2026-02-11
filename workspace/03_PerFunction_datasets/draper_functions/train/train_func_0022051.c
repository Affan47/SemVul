iconInternal(NETRArray<NETIcon> &icons, int icon_count, int width, int height) const
{
    NETIcon result;
    if (!icon_count) {
        result.size.width = 0;
        result.size.height = 0;
        result.data = 0;
        return result;
    }
    result = icons[0];


    if (width == height && height == -1) return result;
    int i;
    for (i = 0; i < icons.size(); i++) {
        if ((icons[i].size.width >= width &&
             icons[i].size.width < result.size.width) &&
             (icons[i].size.height >= height &&
             icons[i].size.height < result.size.height))
            result = icons[i];
    }
    return result;
}
