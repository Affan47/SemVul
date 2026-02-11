caching_an_outline_font(const gs_state * pgs)
{
    return pgs->in_cachedevice > 1 &&
            pgs->font != NULL &&
            pgs->font->FontType != ft_user_defined &&
            pgs->font->FontType != ft_PCL_user_defined &&
            pgs->font->FontType != ft_GL2_stick_user_defined &&
            pgs->font->FontType != ft_CID_user_defined;
}
