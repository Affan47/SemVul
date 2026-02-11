work_space_ensure_size(WorkSpace *wspace,
                      guint len)
{
    if (G_UNLIKELY(len > wspace->size)) {
        wspace->size *= 2;
        wspace->data = g_renew(WorkSpacePoint, wspace->data, wspace->size);
    }
}
