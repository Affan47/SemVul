thread_arg_block (StgFunInfoTable *fun_info, StgClosure **args)
{
    StgPtr p;
    StgWord bitmap;
    W_ size;

    p = (StgPtr)args;
    switch (fun_info->f.fun_type) {
    case ARG_GEN:
	bitmap = BITMAP_BITS(fun_info->f.b.bitmap);
	size = BITMAP_SIZE(fun_info->f.b.bitmap);
	goto small_bitmap;
    case ARG_GEN_BIG:
	size = GET_FUN_LARGE_BITMAP(fun_info)->size;
	thread_large_bitmap(p, GET_FUN_LARGE_BITMAP(fun_info), size);
	p += size;
	break;
    default:
	bitmap = BITMAP_BITS(stg_arg_bitmaps[fun_info->f.fun_type]);
	size = BITMAP_SIZE(stg_arg_bitmaps[fun_info->f.fun_type]);
    small_bitmap:
	while (size > 0) {
	    if ((bitmap & 1) == 0) {
		thread((StgClosure **)p);
	    }
	    p++;
	    bitmap = bitmap >> 1;
	    size--;
	}
	break;
    }
    return p;
}
