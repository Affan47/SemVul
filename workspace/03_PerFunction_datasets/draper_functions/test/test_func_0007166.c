ompi_io_ompio_break_file_view (mca_io_ompio_file_t *fh,
                                   struct iovec *iov,
                                   int count,
                                   int stripe_count,
                                   size_t stripe_size,
                                   struct iovec **broken_iov,
                                   int *broken_count)
{


    struct iovec *temp_iov = NULL;
    int i = 0;
    int k = 0;
    int block = 1;
    int broken = 0;
    size_t remaining = 0;
    size_t temp = 0;
    OPAL_PTRDIFF_TYPE current_offset = 0;


    temp_iov = (struct iovec *) malloc
        (count * sizeof (struct iovec));
    if (NULL == temp_iov) {
        opal_output(1, "OUT OF MEMORY\n");
        return OMPI_ERR_OUT_OF_RESOURCE;
    }

    while (i < count) {
        if (count*block <= k) {
            block ++;
            temp_iov = (struct iovec *)realloc
                (temp_iov, count * block *sizeof(struct iovec));
            if (NULL == temp_iov) {
                opal_output(1, "OUT OF MEMORY\n");
                return OMPI_ERR_OUT_OF_RESOURCE;
            }
        }
        if (0 == broken) {
            temp = (OPAL_PTRDIFF_TYPE)(iov[i].iov_base)%stripe_size;
            if ((stripe_size-temp) >= iov[i].iov_len) {
                temp_iov[k].iov_base = iov[i].iov_base;
                temp_iov[k].iov_len = iov[i].iov_len;
                i++;
                k++;
            }
            else {
                temp_iov[k].iov_base = iov[i].iov_base;
                temp_iov[k].iov_len = stripe_size-temp;
                current_offset = (OPAL_PTRDIFF_TYPE)(temp_iov[k].iov_base) +
                    temp_iov[k].iov_len;
                remaining = iov[i].iov_len - temp_iov[k].iov_len;
                k++;
                broken ++;
            }
            continue;
        }
        temp = current_offset%stripe_size;
        if ((stripe_size-temp) >= remaining) {
            temp_iov[k].iov_base = (IOVBASE_TYPE *)current_offset;
            temp_iov[k].iov_len = remaining;
            i++;
            k++;
            broken = 0;
            current_offset = 0;
            remaining = 0;
        }
        else {
            temp_iov[k].iov_base = (IOVBASE_TYPE *)current_offset;
            temp_iov[k].iov_len = stripe_size-temp;
            current_offset += temp_iov[k].iov_len;
            remaining -= temp_iov[k].iov_len;
            k++;
            broken ++;
        }
    }
    *broken_iov = temp_iov;
    *broken_count = k;

    return 1;
}
