zmbv_me(ZmbvEncContext *c, uint8_t *src, int sstride, uint8_t *prev, int pstride,
                    int x, int y, int *mx, int *my)
{
    int dx, dy, tx, ty, tv, bv, bw, bh;

    *mx = *my = 0;
    bw = FFMIN(ZMBV_BLOCK, c->avctx->width - x);
    bh = FFMIN(ZMBV_BLOCK, c->avctx->height - y);
    bv = block_cmp(src, sstride, prev, pstride, bw, bh);
    if(!bv) return 0;
    for(ty = FFMAX(y - c->range, 0); ty < FFMIN(y + c->range, c->avctx->height - bh); ty++){
        for(tx = FFMAX(x - c->range, 0); tx < FFMIN(x + c->range, c->avctx->width - bw); tx++){
            if(tx == x && ty == y) continue;
            dx = tx - x;
            dy = ty - y;
            tv = block_cmp(src, sstride, prev + dx + dy*pstride, pstride, bw, bh);
            if(tv < bv){
                 bv = tv;
                 *mx = dx;
                 *my = dy;
                 if(!bv) return 0;
             }
         }
    }
    return bv;
}
