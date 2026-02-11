create_float_dataset(hid_t fid, const char *dsidx, int fulldims)
{
    int     rank = RANK;
    int     rankds = 1;
    hsize_t dims[RANK]  = {DIM1_SIZE,DIM2_SIZE};
    float   buf[DIM1_SIZE*DIM2_SIZE];
    hsize_t s1_dim[1]  = {DIM1_SIZE};
    hsize_t s2_dim[1]  = {DIM2_SIZE};
    float   s1_wbuf[DIM1_SIZE] = {10,20,30};
    float   s11_wbuf[DIM1_SIZE] = {10,100,300};
    float   s2_wbuf[DIM2_SIZE] = {100,200,300,400};
    float   s21_wbuf[DIM2_SIZE] = {10,20,30,40};
    float   s22_wbuf[DIM2_SIZE] = {5,10,50,300};
    char name[32];

    HDstrcpy(name, DATASET_NAME);
    HDstrcat(name, dsidx);


    if(H5LTmake_dataset_float(fid, name, rank, dims, buf) >= 0) {
        if(fulldims==0) {

            if(create_DS1_float_datasets(fid, dsidx, rankds, s1_dim, s1_wbuf, NULL) < 0)
             return FAIL;


            if(create_DS2_float_datasets(fid, dsidx, rankds, s2_dim, s2_wbuf, NULL, NULL) < 0)
             return FAIL;
        }
        else {
            if(create_DS1_float_datasets(fid, dsidx, rankds, s1_dim, s1_wbuf, s11_wbuf) < 0)
             return FAIL;

            if(create_DS2_float_datasets(fid, dsidx, rankds, s2_dim, s2_wbuf, s21_wbuf, s22_wbuf) < 0)
             return FAIL;
        }
     }
     else
         return FAIL;
    return SUCCEED;
}
