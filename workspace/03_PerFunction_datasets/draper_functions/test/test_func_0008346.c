is_set_recursive(resource_t * rsc, long long flag, bool any)
{
    GListPtr gIter;
    bool all = !any;

    if(is_set(rsc->flags, flag)) {
        if(any) {
            return TRUE;
        }
    } else if(all) {
        return FALSE;
    }

    for (gIter = rsc->children; gIter != NULL; gIter = gIter->next) {
        if(is_set_recursive(gIter->data, flag, any)) {
            if(any) {
                return TRUE;
            }

        } else if(all) {
            return FALSE;
        }
    }

    if(all) {
        return TRUE;
    }
    return FALSE;
}
