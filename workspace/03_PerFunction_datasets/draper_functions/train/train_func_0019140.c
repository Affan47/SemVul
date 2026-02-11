bd_get_current_chapter(BLURAY *bd)
{
    uint32_t ret = 0;

    bd_mutex_lock(&bd->mutex);

    if (bd->title) {
        ret = nav_chapter_get_current(bd->st0.clip, SPN(bd->st0.clip_pos));
    }

    bd_mutex_unlock(&bd->mutex);

    return ret;
}
