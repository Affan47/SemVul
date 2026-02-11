apply(apply_fp_t fp, void *param)
{
    return (e0 ? (*fp)(e0, param) : 0) ||
           condApply(exps, fp, param) ||
           (*fp)(this, param);
}
