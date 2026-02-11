posix_buffer_write(int local_dim, file_descr *fd, parameters *parms, void *buffer)
{
    int dtype_size = 1;
    int         ret_code = SUCCESS;
    long i;
    size_t d_offset;
    size_t linear_dset_offset = 0;
    int j, rc;


    if (local_dim < parms->rank-1 && local_dim != cont_dim) {

        for (i=0; i < parms->buf_size[local_dim]; i += dtype_size) {
            buf_offset[local_dim] = i;
            posix_buffer_write(local_dim+1, fd, parms, buffer);


            if (local_dim+1==cont_dim)
                break;
        }

    } else {

        buf_offset[local_dim] = 0;


        for (i=0; i < parms->rank; i++){
            d_offset=1;

            for (j=i+1; j < parms->rank; j++)
                d_offset *= parms->dset_size[j];

            linear_dset_offset += (offset[i]+buf_offset[i])*d_offset;
        }


        rc = POSIXSEEK(fd->posixfd, linear_dset_offset) < 0 ? -1 : 0;
        VRFY((rc==0), "POSIXSEEK");

        rc = ((ssize_t)cont_size ==
             POSIXWRITE(fd->posixfd, buf_p, cont_size));
        VRFY((rc != 0), "POSIXWRITE");


        buf_p += cont_size;

    }
done:
    return ret_code;
}
