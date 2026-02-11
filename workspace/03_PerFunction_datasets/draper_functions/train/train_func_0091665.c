H5FD_multi_init(void)
{

    H5Eclear2(H5E_DEFAULT);

    if (H5I_VFL!=H5Iget_type(H5FD_MULTI_g)) {
	H5FD_MULTI_g = H5FDregister(&H5FD_multi_g);
    }
    return H5FD_MULTI_g;
}
