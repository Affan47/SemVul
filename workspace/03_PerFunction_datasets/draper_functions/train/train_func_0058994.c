Z_ChangeTag2(void *ptr, int tag, char *file, int line)
{
    memblock_t*	block;

    block = (memblock_t *) ((byte *)ptr - sizeof(memblock_t));

    if (block->id != ZONEID)
        I_Error("%s:%i: Z_ChangeTag: block without a ZONEID!",
                file, line);

    if (tag >= PU_PURGELEVEL && block->user == NULL)
        I_Error("%s:%i: Z_ChangeTag: an owner is required "
                "for purgable blocks", file, line);


    Z_RemoveBlock(block);
    block->tag = tag;
    Z_InsertBlock(block);
}
