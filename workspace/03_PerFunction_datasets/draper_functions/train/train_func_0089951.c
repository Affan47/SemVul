find_kern(font_data *font, int lindex, int rindex)
{
    kern_pair wantkp;
    kern_pair const *kp;

    if (lindex == NOGLYPH || rindex == NOGLYPH)
	return 0;
    wantkp.left = lindex;
    wantkp.right = rindex;
    kp = find234(font->info->kerns, &wantkp, NULL);
    if (kp == NULL)
	return 0;
    return kp->kern;
}
