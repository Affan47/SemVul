get_block(OPDBlock *block, const guchar **p)
{
    memset(block->name, 0, BLOCK_NAME_SIZE + 1);
    strncpy(block->name, *p, BLOCK_NAME_SIZE);
    *p += BLOCK_NAME_SIZE;
    g_strstrip(block->name);
    block->type = gwy_get_guint16_le(p);
    block->size = gwy_get_guint32_le(p);
    block->flags = gwy_get_guint16_le(p);

    if (strncmp(block->name, "AdjustVSI_", sizeof("AdjustVSI_")-1) == 0
        && block->type == 7
        && block->size == 2) {
        g_warning("Changing the type of field %s from float to short.",
                  block->name);
        block->type = 6;
    }
}
