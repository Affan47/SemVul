bdrv_flush(BlockDriverState *bs)
{
    if (bs->drv->bdrv_flush)
        bs->drv->bdrv_flush(bs);
    if (bs->backing_hd)
        bdrv_flush(bs->backing_hd);
}
