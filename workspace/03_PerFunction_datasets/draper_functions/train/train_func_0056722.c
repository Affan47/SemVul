h5tools_str_region_prefix(h5tools_str_t *str, const h5tool_format_t *info,
        hsize_t elmtno, hsize_t *ptdata, unsigned ndims, hsize_t max_idx[],
        h5tools_context_t *ctx)
{
    hsize_t p_prod[H5S_MAX_RANK];
    size_t i = 0;
    hsize_t curr_pos = elmtno;

    h5tools_str_reset(str);

    if (ndims > 0) {


        for (i = ndims - 1, p_prod[ndims - 1] = 1; i > 0; --i)
            p_prod[i - 1] = (max_idx[i]) * p_prod[i];

        for (i = 0; i < (size_t) ndims; i++) {
            if(curr_pos > 0) {
                ctx->pos[i] = curr_pos / p_prod[i];
                curr_pos -= p_prod[i] * ctx->pos[i];
            }
            else
                ctx->pos[i] = 0;
            ctx->pos[i] += (unsigned long) ptdata[ctx->sm_pos+i];
        }


        for (i = 0; i < (size_t) ndims; i++) {
            if (i)
                h5tools_str_append(str, "%s", OPT(info->idx_sep, ","));

            h5tools_str_append(str, OPT(info->idx_n_fmt, HSIZE_T_FORMAT), (hsize_t) ctx->pos[i]);

        }
    }
    else {

        h5tools_str_append(str, OPT(info->idx_n_fmt, HSIZE_T_FORMAT), (hsize_t) 0);
    }


    return h5tools_str_fmt(str, 0, OPT(info->idx_fmt, "%s: "));
}
