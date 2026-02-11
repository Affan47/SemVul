H5S_get_select_hyper_blocklist(H5S_t *space, hbool_t internal, hsize_t startblock, hsize_t numblocks, hsize_t *buf)
{
    H5S_hyper_dim_t *diminfo;
    hsize_t tmp_count[H5O_LAYOUT_NDIMS];
    hsize_t offset[H5O_LAYOUT_NDIMS];
    hsize_t start[H5O_LAYOUT_NDIMS];
    hsize_t end[H5O_LAYOUT_NDIMS];
    hsize_t temp_off;
    int i;
    int fast_dim;
    int temp_dim;
    int ndims;
    int done;
    herr_t ret_value=SUCCEED;

    FUNC_ENTER_NOAPI_NOINIT_NOFUNC(H5S_get_select_hyper_blocklist);

    assert(space);
    assert(buf);


    if(space->select.sel_info.hslab->diminfo_valid) {

        ndims=space->extent.rank;
        fast_dim=ndims-1;


        if(internal)


            diminfo=space->select.sel_info.hslab->opt_diminfo;
        else


            diminfo=space->select.sel_info.hslab->app_diminfo;


        for(i=0; i<ndims; i++) {
            tmp_count[i]=diminfo[i].count;
            offset[i]=diminfo[i].start;
        }


        done=0;


        while(done==0 && numblocks>0) {

            while(tmp_count[fast_dim]>0 && numblocks>0) {


                if(startblock==0) {

                    HDmemcpy(buf,offset,sizeof(hsize_t)*ndims);
                    buf+=ndims;


                    HDmemcpy(buf,offset,sizeof(hsize_t)*ndims);
                    for(i=0; i<ndims; i++)
                        buf[i]+=(diminfo[i].block-1);
                    buf+=ndims;


                    numblocks--;
                }
                else
                    startblock--;


                offset[fast_dim]+=diminfo[fast_dim].stride;


                tmp_count[fast_dim]--;
            }


            if(fast_dim>0 && numblocks>0) {

                tmp_count[fast_dim]=diminfo[fast_dim].count;


                temp_dim=fast_dim-1;
                while(temp_dim>=0 && done==0) {

                    tmp_count[temp_dim]--;


                    if(tmp_count[temp_dim]>0)
                        break;


                    if(temp_dim==0)
                        done=1;


                    tmp_count[temp_dim]=diminfo[temp_dim].count;


                    temp_dim--;
                }
            }


            for(i=0; i<ndims; i++) {
                temp_off=diminfo[i].start+diminfo[i].stride*(diminfo[i].count-tmp_count[i]);
                offset[i]=temp_off;
            }
        }
    }
    else
        ret_value=H5S_hyper_span_blocklist(space->select.sel_info.hslab->span_lst,start,end,(hsize_t)0,&startblock,&numblocks,&buf);

    FUNC_LEAVE_NOAPI(ret_value);
}
