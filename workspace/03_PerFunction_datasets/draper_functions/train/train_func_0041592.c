get_baa_by_block_id(List *baa_list, int loopno)
{
    BlockAlignArray *baa = NULL;
    List *li;

    for (li = baa_list; li != NULL; li = li->next) {
        baa = li->data;
        if (baa->block->no == loopno)
            break;
    }

    return baa;
}
