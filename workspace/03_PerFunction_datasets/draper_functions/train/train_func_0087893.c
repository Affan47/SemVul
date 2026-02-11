get_banner_info(os_banner_info_t *info)
{
    int ret;


    ret = os_banner_getinfo(banner_, info);


    if (ret)
    {


        switch(win_type_)
        {
        case OS_BANNER_TYPE_TEXTGRID:


            info->style &= ~OS_BANNER_STYLE_TAB_ALIGN;
            break;

        default:

            break;
        }
    }


    return ret;
}
