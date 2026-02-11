alloc_rec(VMG0_)
{


    for (;;)
    {


        if (savept_cnt_ == 0 || next_free_ != oldest_first_)
        {
            CVmUndoMeta *ret;


            ret = next_free_;


            inc_rec_ptr(&next_free_);


            return ret;
        }


        if (savept_cnt_ > 1)
        {


            drop_oldest_savept(vmg0_);
        }
        else
        {


            drop_oldest_savept(vmg0_);
            return 0;
        }
    }
}
