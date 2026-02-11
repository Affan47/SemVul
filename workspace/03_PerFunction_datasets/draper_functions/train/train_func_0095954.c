save_to_file(VMG_ class CVmFile *fp)
{
    vm_lookup_ext *ext = get_ext();
    uint i;
    vm_lookup_val **bp;
    vm_lookup_val *val;


    fp->write_int2(ext->bucket_cnt);
    fp->write_int2(ext->value_cnt);
    fp->write_int2(ext->val_to_img_idx(ext->first_free));


    for (i = ext->bucket_cnt, bp = ext->buckets ; i != 0 ; --i, ++bp)
        fp->write_int2(ext->val_to_img_idx(*bp));


    for (i = ext->value_cnt, val = ext->idx_to_val(0) ; i != 0 ; --i, ++val)
    {
        char buf[VMLOOKUP_VALUE_SIZE];
        uint idx;


        vmb_put_dh(buf, &val->key);
        vmb_put_dh(buf + VMB_DATAHOLDER, &val->val);
        idx = ext->val_to_img_idx(val->nxt);
        oswp2(buf + VMB_DATAHOLDER*2, idx);


        fp->write_bytes(buf, VMLOOKUP_VALUE_SIZE);
    }
}
