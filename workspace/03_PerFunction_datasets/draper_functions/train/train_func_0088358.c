alloc_mem(size_t siz, ulong remaining_in_page)
{


    if (siz > VMIMAGE_EXT_BLK_SIZE / 8)
    {
        CVmImageFileExt_blk *new_block;


        new_block = new CVmImageFileExt_blk(siz);


        new_block->nxt_ = 0;
        new_block->prv_ = mem_tail_;


        if (mem_tail_ != 0)
            mem_tail_->nxt_ = new_block;
        else
            mem_head_ = new_block;


        mem_tail_ = new_block;


        return mem_tail_->suballoc(siz);
    }
    else
    {


        if (mem_head_ == 0 || siz > mem_head_->rem_)
        {
            CVmImageFileExt_blk *new_block;
            size_t new_block_size;


            new_block_size = VMIMAGE_EXT_BLK_SIZE;
            if (new_block_size > remaining_in_page)
                new_block_size = (size_t)remaining_in_page;


            new_block = new CVmImageFileExt_blk(new_block_size);


            new_block->prv_ = 0;
            new_block->nxt_ = mem_head_;


            if (mem_head_ != 0)
                mem_head_->prv_ = new_block;
            else
                mem_tail_ = new_block;


            mem_head_ = new_block;
        }


        return mem_head_->suballoc(siz);
    }
}
