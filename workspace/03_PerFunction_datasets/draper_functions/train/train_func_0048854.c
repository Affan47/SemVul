virtual_hook( int id, void* data )
{


    switch (id) {
        case 0: {
                bool *enable = static_cast<bool*>(data);
                d->confirmOverwrite = *enable;
            }
            break;
        case 1: {
                bool *show = static_cast<bool*>(data);
                d->setInlinePreviewShown(*show);
            }
            break;
        default:
            break;
    }
}
